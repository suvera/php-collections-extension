
extern PHP_METHOD(StdMap, __construct);
extern PHP_METHOD(StdMap, size);
extern PHP_METHOD(StdMap, reserve);
extern PHP_METHOD(StdMap, at);
extern PHP_METHOD(StdMap, push);
extern PHP_METHOD(StdMap, erase);
extern PHP_METHOD(StdMap, clear);
extern PHP_METHOD(StdMap, hasKey);
extern PHP_METHOD(StdMap, hasValue);
extern PHP_METHOD(StdMap, search);
extern PHP_METHOD(StdMap, getClass);
extern PHP_METHOD(StdMap, keys);
extern PHP_METHOD(StdMap, values);

// iterator
extern PHP_METHOD(StdMap, applyEach);

// Take other StdMap as input append to elements into this
extern PHP_METHOD(StdMap, append);

// Take other StdMap as input and return StdMap
extern PHP_METHOD(StdMap, merge);
extern PHP_METHOD(StdMap, intersect);
extern PHP_METHOD(StdMap, diff);

// Implement Serializable
extern PHP_METHOD(StdMap, serialize);
extern PHP_METHOD(StdMap, unserialize);


static zend_function_entry map_class_methods[] = {
    PHP_ME(StdMap, size, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, reserve, arginfo_vector_reserve, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, at, arginfo_vector_at, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, push, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, erase, arginfo_vector_erase, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, keys, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, values, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, getClass, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, hasKey, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, hasValue, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, search, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdMap, __construct, arginfo_vector_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

	/* Aliases */
    PHP_MALIAS(StdMap, replace, push, arginfo_vector_add, ZEND_ACC_PUBLIC)

    PHP_ME(StdMap, applyEach, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdMap, append, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, merge, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, intersect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, diff, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdMap, serialize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdMap, unserialize, arginfo_unserialize, ZEND_ACC_PUBLIC)

	PHP_FE_END
};


// Map Methods
static void map_object_free_storage(map_object *intern TSRMLS_DC)
{
    if (intern->vo != NULL) {
        switch (intern->type) {
            case TYPE_SCALAR_INT:
            {
                IntStdMap *tmp = static_cast<IntStdMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatStdMap *tmp = static_cast<FloatStdMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_STRING:
            {
                StringStdMap *tmp = static_cast<StringStdMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_BOOL:
            {
                BoolStdMap *tmp = static_cast<BoolStdMap*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdMap *tmp = static_cast<ZvalStdMap*>(intern->vo);

                for (auto it = tmp->cbegin(); it != tmp->cend(); ++it ) {
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
static zend_object_value map_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;

	/* Allocate memory for it */
	map_object *intern = (map_object*) emalloc(sizeof(map_object));
	memset(intern, 0, sizeof(map_object));

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);

	retval.handle = zend_objects_store_put(
	    intern,
	    (zend_objects_store_dtor_t) zend_objects_destroy_object,
	    (zend_objects_free_object_storage_t) map_object_free_storage,
	    NULL TSRMLS_CC
	);

	retval.handlers = (zend_object_handlers *) &map_handlers;

	intern->type = 0;
    intern->vo = NULL;
    intern->objCe = NULL;

	return retval;
}