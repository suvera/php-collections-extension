typedef unordered_set<long> IntStdSet;
typedef unordered_set<double> FloatStdSet;
typedef unordered_set<string> StringStdSet;
typedef unordered_set<bool> BoolStdSet;
typedef unordered_set<zval*, std::hash<zval*>, zvalCompareIdentical> ZvalStdSet;


typedef struct _set_object {
    zend_object std;
    int type;
    void *vo;
    long ptr;
    zend_class_entry *objCe;
} set_object;


extern PHP_METHOD(StdSet, __construct);
extern PHP_METHOD(StdSet, size);
extern PHP_METHOD(StdSet, reserve);
extern PHP_METHOD(StdSet, push);
extern PHP_METHOD(StdSet, erase);
extern PHP_METHOD(StdSet, clear);
extern PHP_METHOD(StdSet, hasValue);
extern PHP_METHOD(StdSet, getClass);
extern PHP_METHOD(StdSet, values);

// iterator
extern PHP_METHOD(StdSet, applyEach);

// Take other StdSet as input append to elements into this
extern PHP_METHOD(StdSet, append);

// Take other StdSet as input and return StdSet
extern PHP_METHOD(StdSet, merge);
extern PHP_METHOD(StdSet, intersect);
extern PHP_METHOD(StdSet, diff);

static zend_function_entry set_class_methods[] = {
    PHP_ME(StdSet, size, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSet, reserve, arginfo_vector_reserve, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, push, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, erase, arginfo_vector_erase, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, values, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, getClass, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, hasValue, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdSet, __construct, arginfo_vector_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

    PHP_ME(StdSet, applyEach, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdSet, append, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSet, merge, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSet, intersect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdSet, diff, NULL, ZEND_ACC_PUBLIC)

	PHP_FE_END
};


// Set Methods
static void set_object_free_storage(set_object *intern TSRMLS_DC)
{
    if (intern->vo != NULL) {
        switch (intern->type) {
            case TYPE_SCALAR_INT:
            {
                IntStdSet *tmp = static_cast<IntStdSet*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatStdSet *tmp = static_cast<FloatStdSet*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_STRING:
            {
                StringStdSet *tmp = static_cast<StringStdSet*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_BOOL:
            {
                BoolStdSet *tmp = static_cast<BoolStdSet*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdSet *tmp = static_cast<ZvalStdSet*>(intern->vo);

                for (auto it = tmp->cbegin(); it != tmp->cend(); ++it ) {
                    delete_reference_count(*it);
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

// Set Methods
static zend_object_value set_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;

	/* Allocate memory for it */
	set_object *intern = (set_object*) emalloc(sizeof(set_object));
	memset(intern, 0, sizeof(set_object));

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);

	retval.handle = zend_objects_store_put(
	    intern,
	    (zend_objects_store_dtor_t) zend_objects_destroy_object,
	    (zend_objects_free_object_storage_t) set_object_free_storage,
	    NULL TSRMLS_CC
	);

	retval.handlers = (zend_object_handlers *) &set_handlers;

	intern->type = 0;
    intern->vo = NULL;
    intern->objCe = NULL;

	return retval;
}