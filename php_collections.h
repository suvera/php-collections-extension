/* ---------------------------------------------------------------------------
** see LICENSE.md
**
** php_collections.h
** StdVector Implementation
**
** Author: rnarmala
** -------------------------------------------------------------------------*/

#ifndef PHP_COLLECTIONS_H
#define PHP_COLLECTIONS_H


extern zend_module_entry collections_module_entry;
#define phpext_collections_ptr &collections_module_entry

#define PHP_COLLECTIONS_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_COLLECTIONS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_COLLECTIONS_API __attribute__ ((visibility("default")))
#else
#	define PHP_COLLECTIONS_API
#endif

extern "C" {
#ifdef ZTS
#include "TSRM.h"
#endif

//#include "zend_API.h"
#include "ext/standard/php_var.h"
#include "ext/standard/php_smart_str.h"
//#include "ext/standard/php_array.h"
#include "zend_interfaces.h"
#include "zend_exceptions.h"
}

#define TYPE_SCALAR_INT 1
#define TYPE_SCALAR_FLOAT 2
#define TYPE_SCALAR_STRING 3
#define TYPE_SCALAR_BOOL 4
#define TYPE_COMPLEX_RESOURCE 5
#define TYPE_COMPLEX_OBJECT 6
#define TYPE_COMPLEX_ARRAY 7

#define DEFAULT_CAPACITY 10

#define VECTOR_CLASS_NAME "StdVector"
#define MAP_CLASS_NAME "StdMap"
#define SET_CLASS_NAME "StdSet"

typedef unsigned long uLongInt;

typedef vector<long> IntVector;
typedef vector<double> FloatVector;
typedef vector<bool> BoolVector;
typedef vector<string> StringVector;
typedef vector<zval*> ZvalVector;

typedef unordered_map<string, long> IntStdMap;
typedef unordered_map<string, double> FloatStdMap;
typedef unordered_map<string, string> StringStdMap;
typedef unordered_map<string, bool> BoolStdMap;
typedef unordered_map<string, zval*> ZvalStdMap;

typedef std::pair<const string, long> IntStdPair;
typedef std::pair<const string, double> FloatStdPair;
typedef std::pair<const string, string> StringStdPair;
typedef std::pair<const string, bool> BoolStdPair;
typedef std::pair<const string, zval*> ZvalStdPair;

typedef std::pair<const char* const, long> IntStdSuperPair;
typedef std::pair<const char* const, double> FloatStdSuperPair;
typedef std::pair<const char* const, string> StringStdSuperPair;
typedef std::pair<const char* const, bool> BoolStdSuperPair;
typedef std::pair<const char* const, zval*> ZvalStdSuperPair;

typedef struct _vector_object {
    zend_object std;
    int type;
    void *vo;
    long ptr;
    zend_class_entry *objCe;
} vector_object;

typedef struct _map_object {
    zend_object std;
    int type;
    void *vo;
    long ptr;
    zend_class_entry *objCe;
} map_object;

PHP_MINIT_FUNCTION(collections);
PHP_MSHUTDOWN_FUNCTION(collections);
PHP_RINIT_FUNCTION(collections);
PHP_RSHUTDOWN_FUNCTION(collections);
PHP_MINFO_FUNCTION(collections);




#ifdef ZTS
#define COLLECTIONS_G(v) TSRMG(collections_globals_id, zend_collections_globals *, v)
#else
#define COLLECTIONS_G(v) (collections_globals.v)
#endif

#endif

