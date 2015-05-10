/* ---------------------------------------------------------------------------
** see LICENSE.md
**
** std_vector.h
** StdVector Implementation
**
** Author: rnarmala
** -------------------------------------------------------------------------*/

extern PHP_METHOD(StdVector, __construct);
extern PHP_METHOD(StdVector, size);
extern PHP_METHOD(StdVector, reserve);
extern PHP_METHOD(StdVector, at);
extern PHP_METHOD(StdVector, push);
extern PHP_METHOD(StdVector, replace);
extern PHP_METHOD(StdVector, insert);
extern PHP_METHOD(StdVector, erase);
extern PHP_METHOD(StdVector, clear);
extern PHP_METHOD(StdVector, sort);
extern PHP_METHOD(StdVector, search);
extern PHP_METHOD(StdVector, getClass);

// search value from last
extern PHP_METHOD(StdVector, searchLast);
// Reverse  this vector
extern PHP_METHOD(StdVector, reverse);

//Apply function to all elements in this vector
extern PHP_METHOD(StdVector, applyEach);
//Count appearances of value in this vector
extern PHP_METHOD(StdVector, countValue);
// fill with values
extern PHP_METHOD(StdVector, fill);
// Make Unique
extern PHP_METHOD(StdVector, unique);

// iterator
extern PHP_METHOD(StdVector, hasNext);
extern PHP_METHOD(StdVector, hasPrev);
extern PHP_METHOD(StdVector, moveFirst);
extern PHP_METHOD(StdVector, moveLast);
extern PHP_METHOD(StdVector, getPointer);
extern PHP_METHOD(StdVector, getIndex);
extern PHP_METHOD(StdVector, getValue);
extern PHP_METHOD(StdVector, seek);

// Take other StdVector as input append to elements into this
extern PHP_METHOD(StdVector, append);

// Take other StdVector as input and return StdVector
extern PHP_METHOD(StdVector, merge);
extern PHP_METHOD(StdVector, intersect);
extern PHP_METHOD(StdVector, diff);

// Implement Serializable
extern PHP_METHOD(StdVector, serialize);
extern PHP_METHOD(StdVector, unserialize);

static zend_function_entry vector_class_methods[] = {
    PHP_ME(StdVector, size, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, reserve, arginfo_vector_reserve, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, at, arginfo_vector_at, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, push, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, replace, arginfo_vector_insert, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, insert, arginfo_vector_insert, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, erase, arginfo_vector_erase, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, sort, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, getClass, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, search, arginfo_vector_add, ZEND_ACC_PUBLIC)
	PHP_ME(StdVector, __construct, arginfo_vector_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

    PHP_ME(StdVector, searchLast, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, reverse, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, applyEach, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, countValue, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, fill, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, unique, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, hasNext, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, hasPrev, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, moveFirst, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, moveLast, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, getPointer, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, getIndex, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, getValue, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, seek, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, append, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, merge, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, intersect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, diff, NULL, ZEND_ACC_PUBLIC)

    PHP_ME(StdVector, serialize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(StdVector, unserialize, arginfo_unserialize, ZEND_ACC_PUBLIC)

	PHP_FE_END
};


// Vector
static void vector_object_free_storage(vector_object *intern TSRMLS_DC)
{
    if (intern->vo != NULL) {
        switch (intern->type) {
            case TYPE_SCALAR_INT:
            {
                IntVector *tmp = static_cast<IntVector*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatVector *tmp = static_cast<FloatVector*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_STRING:
            {
                StringVector *tmp = static_cast<StringVector*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_SCALAR_BOOL:
            {
                BoolVector *tmp = static_cast<BoolVector*>(intern->vo);
                tmp->clear();
                delete tmp;
            }
            break;
            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalVector *tmp = static_cast<ZvalVector*>(intern->vo);

                std::for_each(tmp->begin(), tmp->end(), delete_reference_count);

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

// Vector
static zend_object_value vector_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value retval;

	/* Allocate memory for it */
	vector_object *intern = (vector_object*) emalloc(sizeof(vector_object));
	memset(intern, 0, sizeof(vector_object));

	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
	object_properties_init(&intern->std, class_type);

	retval.handle = zend_objects_store_put(
	    intern,
	    (zend_objects_store_dtor_t) zend_objects_destroy_object,
	    (zend_objects_free_object_storage_t) vector_object_free_storage,
	    NULL TSRMLS_CC
	);

	retval.handlers = (zend_object_handlers *) &vector_handlers;

	intern->type = 0;
	intern->ptr = 0;
    intern->vo = NULL;
    intern->objCe = NULL;

	return retval;
}