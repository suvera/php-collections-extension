#if defined(HAVE_GOOGLE_LOCAL) || defined(HAVE_GOOGLE_LOCAL)

/* for StdSet */
static zend_object_handlers super_map_handlers;
zend_class_entry *super_map_entry;

#define SUPER_MAP_CLASS_NAME "StdSuperMap"

#define SUPER_MAP_EMPTY_KEY NULL
//"<* _`[(^%#@&eMpTy&@# %^)]`_*>"
#define SUPER_MAP_DELETED_KEY "<* _`[(^%#@&DeLeTED&@# %^)]`_*>"

#include <google/dense_hash_map>
using std::tr1::hash;
using google::dense_hash_map;


// ######################################################################################################################
struct CharPtrEquality {
    bool operator()(const char* s1, const char* s2) const {
        if (s1 && s2)
            return strcmp(s1, s2) == 0;
        else if (s1 == NULL && s2 == NULL)
            return true;

        return false;
    }
};

struct CompareCharPtrValue {
    const char *value;
    void*** tsrmls_dc;

    bool operator()(const char* s2) const {
        if (value && s2)
            return strcmp(value, s2) == 0;
        else
            return value == NULL && s2 == NULL;
    }

    CompareCharPtrValue(const char *val, void*** tsrmls_dc_) {
        value = val;
        tsrmls_dc = tsrmls_dc_;
    }
};

bool compareCharPtr(const char* s1, const char* s2) {
    if (s1 && s2)
        return strcmp(s1, s2) == 0;
    else if (s1 == NULL && s2 == NULL)
        return true;
    else if (s1 == NULL)
        return true;
    else
        return false;
}

#define HASH_SEED 5381

// replace in-place of   hash<const char*>  below
struct customHash {
    unsigned long operator()(const char* str) const {
        unsigned long hash = HASH_SEED;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
};
// ######################################################################################################################


typedef dense_hash_map<const char*, long, customHash, CharPtrEquality> IntStdSuperMap;
typedef dense_hash_map<const char*, double, customHash, CharPtrEquality> FloatStdSuperMap;
typedef dense_hash_map<const char*, bool, customHash, CharPtrEquality> BoolStdSuperMap;
typedef dense_hash_map<const char*, string, customHash, CharPtrEquality> StringStdSuperMap;
typedef dense_hash_map<const char*, zval*, customHash, CharPtrEquality> ZvalStdSuperMap;

typedef map_object super_map_object;

extern PHP_METHOD(StdSuperMap, __construct);
extern PHP_METHOD(StdSuperMap, size);
extern PHP_METHOD(StdSuperMap, reserve);
extern PHP_METHOD(StdSuperMap, at);
extern PHP_METHOD(StdSuperMap, push);
extern PHP_METHOD(StdSuperMap, erase);
extern PHP_METHOD(StdSuperMap, clear);
extern PHP_METHOD(StdSuperMap, hasKey);
extern PHP_METHOD(StdSuperMap, hasValue);
extern PHP_METHOD(StdSuperMap, search);
extern PHP_METHOD(StdSuperMap, getClass);
extern PHP_METHOD(StdSuperMap, keys);
extern PHP_METHOD(StdSuperMap, values);

// iterator
extern PHP_METHOD(StdSuperMap, applyEach);

// Take other StdSuperMap as input append to elements into this
extern PHP_METHOD(StdSuperMap, append);

// Take other StdSuperMap as input and return StdSuperMap
extern PHP_METHOD(StdSuperMap, merge);
extern PHP_METHOD(StdSuperMap, intersect);
extern PHP_METHOD(StdSuperMap, diff);

// Implement Serializable
extern PHP_METHOD(StdSuperMap, serialize);
extern PHP_METHOD(StdSuperMap, unserialize);


static zend_function_entry super_map_class_methods[] = {
    PHP_ME(StdSuperMap, size, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, reserve, arginfo_vector_reserve, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, at, arginfo_vector_at, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, push, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, erase, arginfo_vector_erase, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, keys, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, values, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, getClass, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, hasKey, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, hasValue, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, search, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSuperMap, __construct, arginfo_vector_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

	/* Aliases */
    PHP_MALIAS(StdSuperMap, replace, push, arginfo_vector_add, ZEND_ACC_PUBLIC)

    PHP_ME(StdSuperMap, applyEach, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdSuperMap, append, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, merge, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, intersect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, diff, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdSuperMap, serialize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSuperMap, unserialize, arginfo_unserialize, ZEND_ACC_PUBLIC)

	PHP_FE_END
};


// Map Methods
static void super_map_object_free_storage(super_map_object *intern TSRMLS_DC)
{
    if (intern->vo != NULL) {
        switch (intern->type) {
            case TYPE_SCALAR_INT:
            {
                IntStdSuperMap *tmp = static_cast<IntStdSuperMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatStdSuperMap *tmp = static_cast<FloatStdSuperMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_STRING:
            {
                StringStdSuperMap *tmp = static_cast<StringStdSuperMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_BOOL:
            {
                BoolStdSuperMap *tmp = static_cast<BoolStdSuperMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdSuperMap *tmp = static_cast<ZvalStdSuperMap*>(intern->vo);

                for (auto it = tmp->begin(); it != tmp->end(); ++it ) {
                    delete_reference_count(it->second);
                }

                tmp->clear();
                delete tmp;
            }
            break;

            default:
                delete intern->vo;
            break;
        }
    }

    zend_object_std_dtor(&intern->std TSRMLS_CC);

    efree(intern);
}

// Map Methods
static zend_object_value super_map_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;

	/* Allocate memory for it */
	super_map_object *intern = (super_map_object*) emalloc(sizeof(super_map_object));
	memset(intern, 0, sizeof(super_map_object));

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);

	retval.handle = zend_objects_store_put(
	    intern,
	    (zend_objects_store_dtor_t) zend_objects_destroy_object,
	    (zend_objects_free_object_storage_t) super_map_object_free_storage,
	    NULL TSRMLS_CC
	);

	retval.handlers = (zend_object_handlers *) &super_map_handlers;

	intern->type = 0;
    intern->vo = NULL;
    intern->objCe = NULL;

	return retval;
}

#endif