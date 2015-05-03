/* ---------------------------------------------------------------------------
** see LICENSE.md
**
** collections.cpp
** StdVector Implementation
**
** Author: rnarmala
** -------------------------------------------------------------------------*/

#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <memory>
#include <math.h>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>


using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;



#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
}

#include "php_collections.h"



static int le_collections;
/* Class entries & Handlers */
static zend_object_handlers vector_handlers;
zend_class_entry *vector_entry;

/*  for StdMap */
static zend_object_handlers map_handlers;
zend_class_entry *map_entry;


// Method signature Helpers
ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_construct, 0, 0, 2)
	ZEND_ARG_INFO(0, value_type_constant)
	ZEND_ARG_INFO(0, optional_capacity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_add, 0, 0, 1)
	ZEND_ARG_INFO(0, element_to_add)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_at, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_reserve, 0, 0, 1)
	ZEND_ARG_INFO(0, new_capacity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_erase, 0, 0, 2)
	ZEND_ARG_INFO(0, position)
	ZEND_ARG_INFO(0, optional_end_position)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_vector_insert, 0, 0, 2)
	ZEND_ARG_INFO(0, position)
	ZEND_ARG_INFO(0, elements_to_insert)
ZEND_END_ARG_INFO()







static int hash_zval_identical_function(const zval **z1, const zval **z2) /* {{{ */
{
	zval result;
	TSRMLS_FETCH();

	/* is_identical_function() returns 1 in case of identity and 0 in case
	 * of a difference;
	 * whereas this comparison function is expected to return 0 on identity,
	 * and non zero otherwise.
	 */
	if (is_identical_function(&result, (zval *) *z1, (zval *) *z2 TSRMLS_CC)==FAILURE) {
		return 1;
	}
	return !Z_LVAL(result);
}

static void delete_reference_count(zval* val)
{
    if (val == NULL) {
        return;
    }

    Z_DELREF_P(val);

    // destroy zval objects
    if (Z_REFCOUNT_P(val) <= 0) {
        // decrements the refcount for the variable, if no refcounts remain the variable is destroyed
        zval_dtor(val);
    }
}
static void add_reference_count(zval* val)
{
    if (val == NULL) {
        return;
    }

    Z_ADDREF_P(val);
}

struct zvalCompareObject {
};

static bool compareZvalObject(const zval *val1, const zval* val2) {
    if (val1 == NULL && val2 == NULL) {
        return 1;
    } else if (val1 == NULL || val2 == NULL) {
        return 0;
    } else if (Z_OBJ_HT_P(val1) == Z_OBJ_HT_P(val2) && Z_OBJ_HANDLE_P(val1) == Z_OBJ_HANDLE_P(val2)) {
        return 1;
    }

    return 0;
}

static bool compareZvalArray(const zval *val1, const zval* val2) {
    if (val1 == NULL && val2 == NULL) {
        return 1;
    } else if (val1 == NULL || val2 == NULL) {
        return 0;
    } else if (Z_ARRVAL_P(val1) == Z_ARRVAL_P(val2) ||
             zend_hash_compare(Z_ARRVAL_P(val1), Z_ARRVAL_P(val2), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC) == 0 ) {
        return 1;
    }

    return 0;
}

static bool compareZvalResource(const zval *val1, const zval* val2) {
    if (val1 == NULL && val2 == NULL) {
        return 1;
    } else if (val1 == NULL || val2 == NULL) {
        return 0;
    } else if (Z_LVAL_P(val1) == Z_LVAL_P(val2)) {
        return 1;
    }

    return 0;
}

struct CompareZvalValue {
    static int type;

    int operator()(const zval* obj1, const zval* obj2) const {
        switch (CompareZvalValue::type) {
            case TYPE_COMPLEX_RESOURCE:
                return compareZvalResource(obj1, obj2);
            break;

            case TYPE_COMPLEX_OBJECT:
                return compareZvalObject(obj1, obj2);
            break;

            case TYPE_COMPLEX_ARRAY:
                return compareZvalArray(obj1, obj2);
            break;
        }

        return 0;
    }
};

int CompareZvalValue::type = 0;


#include "std_vector.h"
#include "std_map.h"



const zend_function_entry collections_functions[] = {
	PHP_FE_END
};


zend_module_entry collections_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"collections",
	collections_functions,
	PHP_MINIT(collections),
	PHP_MSHUTDOWN(collections),
	PHP_RINIT(collections),	
	PHP_RSHUTDOWN(collections),
	PHP_MINFO(collections),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_COLLECTIONS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_COLLECTIONS
extern "C" {
ZEND_GET_MODULE(collections)
}
#endif





PHP_MINIT_FUNCTION(collections)
{
    zend_class_entry ce;

    /* Register VECTOR_CLASS_NAME Class */
    memcpy(&vector_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    vector_handlers.clone_obj = NULL;
    INIT_CLASS_ENTRY(ce, VECTOR_CLASS_NAME, vector_class_methods);
    vector_entry = zend_register_internal_class(&ce TSRMLS_CC);
    vector_entry->create_object = vector_object_new;



    /* Register MAP_CLASS_NAME Class */
    memcpy(&map_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    map_handlers.clone_obj = NULL;
    INIT_CLASS_ENTRY(ce, MAP_CLASS_NAME, map_class_methods);
    map_entry = zend_register_internal_class(&ce TSRMLS_CC);
    map_entry->create_object = map_object_new;



    // Register PHP Constants
    REGISTER_LONG_CONSTANT("TYPE_SCALAR_INT", TYPE_SCALAR_INT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_SCALAR_FLOAT", TYPE_SCALAR_FLOAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_SCALAR_STRING", TYPE_SCALAR_STRING, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_SCALAR_BOOL", TYPE_SCALAR_BOOL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_COMPLEX_RESOURCE", TYPE_COMPLEX_RESOURCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_COMPLEX_OBJECT", TYPE_COMPLEX_OBJECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("TYPE_COMPLEX_ARRAY", TYPE_COMPLEX_ARRAY, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(collections)
{
	return SUCCESS;
}



PHP_RINIT_FUNCTION(collections)
{
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(collections)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(collections)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "collections support", "enabled");
	php_info_print_table_end();

}



// Implementations
#include "std_vector.cpp"
#include "std_map.cpp"
