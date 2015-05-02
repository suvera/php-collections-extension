/* ---------------------------------------------------------------------------
** see LICENSE.md
**
** std_vector.cpp
** StdVector Implementation
**
** Author: rnarmala
** -------------------------------------------------------------------------*/

PHP_METHOD(StdVector, __construct)
{
    long type = 0, capacity = 0;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &type, &capacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (capacity <= 0)
        capacity = DEFAULT_CAPACITY;

    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (type) {
        case TYPE_SCALAR_INT:
        {
            thisObj->vo = new IntVector();
            ((IntVector*) thisObj->vo)->reserve(capacity);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            thisObj->vo = new FloatVector();
            ((FloatVector*) thisObj->vo)->reserve(capacity);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            thisObj->vo = new StringVector();
            ((StringVector*) thisObj->vo)->reserve(capacity);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            thisObj->vo = new BoolVector();
            ((BoolVector*) thisObj->vo)->reserve(capacity);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            thisObj->vo = new ZvalVector();
            ((ZvalVector*) thisObj->vo)->reserve(capacity);
        }
        break;

        default:
        {
            char buffer[100];
            sprintf(buffer, "Invalid data type %ld", type);
            zend_throw_exception(NULL, buffer, 0 TSRMLS_CC);
        }
        break;
    }

    thisObj->type = type;
}






PHP_METHOD(StdVector, size)
{
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    uLongInt count = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            count = ((IntVector*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            count = ((FloatVector*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            count = ((StringVector*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            count = ((BoolVector*) thisObj->vo)->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            count = ((ZvalVector*) thisObj->vo)->size();
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_LONG(count);
}






PHP_METHOD(StdVector, reserve) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long newCapacity = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &newCapacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (newCapacity <= 0) {
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            ((IntVector*) thisObj->vo)->reserve(newCapacity);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            ((FloatVector*) thisObj->vo)->reserve(newCapacity);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            ((StringVector*) thisObj->vo)->reserve(newCapacity);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            ((BoolVector*) thisObj->vo)->reserve(newCapacity);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ((ZvalVector*) thisObj->vo)->reserve(newCapacity);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}



static bool hasVectorOutOfBounds(const vector_object *thisObj, const long &position) {

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
            return (position < 0 || position >= ((IntVector*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_FLOAT:
            return (position < 0 || position >= ((FloatVector*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_STRING:
            return (position < 0 || position >= ((StringVector*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_BOOL:
            return (position < 0 || position >= ((BoolVector*) thisObj->vo)->size());
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
            return (position < 0 || position >= ((ZvalVector*) thisObj->vo)->size());
        break;
    }

    return false;
}



PHP_METHOD(StdVector, at) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &position) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (hasVectorOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Given Position is not found in the vector.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = ((IntVector*) thisObj->vo)->at(position);
            RETURN_LONG(val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = ((FloatVector*) thisObj->vo)->at(position);
            RETURN_DOUBLE(val);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            string val = ((StringVector*) thisObj->vo)->at(position);
            RETURN_STRING((char *) val.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            bool val = ((BoolVector*) thisObj->vo)->at(position);
            RETURN_BOOL(val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            zval *val = (zval *) ((ZvalVector*) thisObj->vo)->at(position);

            RETVAL_ZVAL(val, 1, 0);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}




PHP_METHOD(StdVector, push) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((IntVector*) thisObj->vo)->push_back(val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((FloatVector*) thisObj->vo)->push_back(val);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            char *val;
            long val_len = 0;

            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &val, &val_len) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((StringVector*) thisObj->vo)->push_back(string(val));
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((BoolVector*) thisObj->vo)->push_back((bool) val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((ZvalVector*) thisObj->vo)->push_back(val);

            add_reference_count(val);
        }
        break;


        case TYPE_COMPLEX_OBJECT:
        {
            zval *val = NULL;
            if (thisObj->objCe == NULL) {
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o!", &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }
            } else {
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O!", &val, thisObj->objCe) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this vector.", 0 TSRMLS_CC);
                    return;
                }
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            if (val != NULL) {
                if (thisObj->objCe == NULL) {
                    thisObj->objCe = Z_OBJCE_P(val);
                }

                vec->push_back(val);

                add_reference_count(val);
            } else {
                vec->push_back(NULL);
            }
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ((ZvalVector*) thisObj->vo)->push_back(val);

            add_reference_count(val);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}


/**
 * Only Applicable to vector<Object>
 */
PHP_METHOD(StdVector, getClass) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->objCe == NULL) {
        RETURN_NULL();
    } else {
        RETURN_STRING((char *) thisObj->objCe->name, 1);
    }
}



// replace
PHP_METHOD(StdVector, replace) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                long val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                IntVector *vec = (IntVector*) thisObj->vo;
                (*vec)[position] = val;
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                double val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                FloatVector *vec = (FloatVector*) thisObj->vo;
                (*vec)[position] = val;
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                char *val;
                long val_len = 0;

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &position, &val, &val_len) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                StringVector *vec = (StringVector*) thisObj->vo;
                (*vec)[position] = val;
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                zend_bool val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lb", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                BoolVector *vec = (BoolVector*) thisObj->vo;
                (*vec)[position] = val;
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            {
                zval *val;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lr", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                (*vec)[position] = val;

                add_reference_count(val);
            }
            break;


            case TYPE_COMPLEX_OBJECT:
            {
                zval *val = NULL;
                if (thisObj->objCe == NULL) {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lo!", &position, &val) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                        return;
                    }
                } else {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lO!", &position, &val, thisObj->objCe) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this vector.", 0 TSRMLS_CC);
                        return;
                    }
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;

                if (val != NULL) {
                    if (thisObj->objCe == NULL) {
                        thisObj->objCe = Z_OBJCE_P(val);
                    }

                    (*vec)[position] = val;

                    add_reference_count(val);
                } else {
                    (*vec)[position] = NULL;
                }

            }
            break;


            case TYPE_COMPLEX_ARRAY:
            {
                zval *val;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                (*vec)[position] = val;

                add_reference_count(val);
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::insert", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}






PHP_METHOD(StdVector, insert) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                long val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                IntVector *vec = (IntVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                double val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                FloatVector *vec = (FloatVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                char *val;
                long val_len = 0;

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &position, &val, &val_len) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                StringVector *vec = (StringVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                zend_bool val = 0;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lb", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                BoolVector *vec = (BoolVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            {
                zval *val;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lr", &position, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);

                add_reference_count(val);
            }
            break;


            case TYPE_COMPLEX_OBJECT:
            {
                zval *val = NULL;
                if (thisObj->objCe == NULL) {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lo!", &position, &val) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                        return;
                    }
                } else {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lO!", &position, &val, thisObj->objCe) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this vector.", 0 TSRMLS_CC);
                        return;
                    }
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;

                if (val != NULL) {
                    if (thisObj->objCe == NULL) {
                        thisObj->objCe = Z_OBJCE_P(val);
                    }

                    vec->insert(vec->begin()+position, val);

                    add_reference_count(val);
                } else {
                    vec->insert(vec->begin()+position, NULL);
                }

            }
            break;


            case TYPE_COMPLEX_ARRAY:
            {
                zval *val;
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "la", &val, &position) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                vec->insert(vec->begin()+position, val);

                add_reference_count(val);
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::insert", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}






PHP_METHOD(StdVector, erase) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0, length = 0, endPosition = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &position, &length) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (length > 0) {
        endPosition = position + length;
    } else {
        endPosition = position + 1;
    }

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                IntVector *vec = (IntVector*) thisObj->vo;
                if (endPosition > vec->size()) endPosition = vec->size();
                vec->erase(vec->begin()+position, vec->begin()+endPosition);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatVector *vec = (FloatVector*) thisObj->vo;
                if (endPosition > vec->size()) endPosition = vec->size();
                vec->erase(vec->begin()+position, vec->begin()+endPosition);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                StringVector *vec = (StringVector*) thisObj->vo;
                if (endPosition > vec->size()) endPosition = vec->size();
                vec->erase(vec->begin()+position, vec->begin()+endPosition);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                BoolVector *vec = (BoolVector*) thisObj->vo;
                if (endPosition > vec->size()) endPosition = vec->size();
                vec->erase(vec->begin()+position, vec->begin()+endPosition);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                if (endPosition > vec->size()) endPosition = vec->size();

                //Z_DELREF_P(new_var);
                std::for_each(vec->begin()+position, vec->begin()+endPosition, delete_reference_count);

                vec->erase(vec->begin()+position, vec->begin()+endPosition);
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::erase", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}





PHP_METHOD(StdVector, clear) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntVector*) thisObj->vo)->clear();
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatVector*) thisObj->vo)->clear();
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringVector*) thisObj->vo)->clear();
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolVector*) thisObj->vo)->clear();
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalVector *vec = (ZvalVector*) thisObj->vo;

                //Z_DELREF_P(new_var);
                std::for_each(vec->begin(), vec->end(), delete_reference_count);

                vec->clear();
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::clear", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}




// Comparison functions

class ObjectSorter {
public:
    zend_fcall_info* fci;
    zend_fcall_info_cache* fci_cache;

    ObjectSorter(zend_fcall_info* fci_, zend_fcall_info_cache* fci_cache_) {
        fci = fci_;
        fci_cache = fci_cache_;
    }

    int operator()(zval* obj1, zval* obj2) const {
        zval **args[2], *retval_ptr = NULL;

        args[0] = &obj1;
        args[1] = &obj2;

        fci->retval_ptr_ptr = &retval_ptr;
        fci->param_count = 2;
        fci->params = args;
        fci->no_separation = 0;

        if (zend_call_function(fci, fci_cache TSRMLS_CC) == SUCCESS) {
            int ret = (int) Z_BVAL_P(retval_ptr);
            if (retval_ptr) {
                zval_ptr_dtor(&retval_ptr);
            }

            return ret;
        }

        return 0;
    }
};




PHP_METHOD(StdVector, sort) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                IntVector *vec = (IntVector*) thisObj->vo;
                std::sort(vec->begin(), vec->end());
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatVector *vec = (FloatVector*) thisObj->vo;
                std::sort(vec->begin(), vec->end());
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                StringVector *vec = (StringVector*) thisObj->vo;
                std::sort(vec->begin(), vec->end());
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                BoolVector *vec = (BoolVector*) thisObj->vo;
                std::sort(vec->begin(), vec->end());
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_ARRAY:
            case TYPE_COMPLEX_OBJECT:
            {
                zend_fcall_info fci;
                zend_fcall_info_cache fci_cache;

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                std::sort(vec->begin(), vec->end(), ObjectSorter(&fci, &fci_cache));
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::sort", 0 TSRMLS_CC);
        return;
    }
}





// search
PHP_METHOD(StdVector, search) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long pos = -1;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector::iterator it = std::find(vec->begin(), vec->end(), val);
            if (it != vec->end()) {
                pos = it - vec->begin();
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector::iterator it = std::find(vec->begin(), vec->end(), val);
            if (it != vec->end()) {
                pos = it - vec->begin();
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            char *val;
            long val_len = 0;

            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &val, &val_len) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector::iterator it = std::find(vec->begin(), vec->end(), string(val));
            if (it != vec->end()) {
                pos = it - vec->begin();
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector::iterator it = std::find(vec->begin(), vec->end(), val);
            if (it != vec->end()) {
                pos = it - vec->begin();
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalResource(*it, val)) {
                    pos = it - vec->begin();
                    break;
                }
            }
        }
        break;


        case TYPE_COMPLEX_OBJECT:
        {
            zval *val = NULL;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o!", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalObject(*it, val)) {
                    pos = it - vec->begin();
                    break;
                }
            }
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalArray(*it, val)) {
                    pos = it - vec->begin();
                    break;
                }
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_LONG(pos);
}




PHP_METHOD(StdVector, searchLast) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long pos = -1;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector::reverse_iterator it = std::find(vec->rbegin(), vec->rend(), val);
            if (it != vec->rend()) {
                pos = it - vec->rbegin();
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector::reverse_iterator it = std::find(vec->rbegin(), vec->rend(), val);
            if (it != vec->rend()) {
                pos = it - vec->rbegin();
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            char *val;
            long val_len = 0;

            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &val, &val_len) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector::reverse_iterator it = std::find(vec->rbegin(), vec->rend(), string(val));
            if (it != vec->rend()) {
                pos = it - vec->rbegin();
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector::reverse_iterator it = std::find(vec->rbegin(), vec->rend(), val);
            if (it != vec->rend()) {
                pos = it - vec->rbegin();
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->crbegin(); it != vec->crend(); ++it) {
                if (Z_LVAL_P(*it) == Z_LVAL_P(val)) {
                    pos = it - vec->rbegin();
                    break;
                }
            }
        }
        break;


        case TYPE_COMPLEX_OBJECT:
        {
            zval *val = NULL;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o!", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            if (val != NULL) {
                for (auto it = vec->crbegin(); it != vec->crend(); ++it) {
                    if (Z_OBJ_HT_P(*it) == Z_OBJ_HT_P(val) && (Z_OBJ_HANDLE_P(*it) == Z_OBJ_HANDLE_P(val))) {
                        pos = it - vec->rbegin();
                        break;
                    }
                }
            } else {
                for (auto it = vec->crbegin(); it != vec->crend(); ++it) {
                    if (*it == NULL) {
                        pos = it - vec->rbegin();
                        break;
                    }
                }
            }
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->crbegin(); it != vec->crend(); ++it) {
                if ((Z_ARRVAL_P(*it) == Z_ARRVAL_P(val)) ||
                    zend_hash_compare(Z_ARRVAL_P(*it), Z_ARRVAL_P(val), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC)==0) {

                    pos = it - vec->rbegin();
                    break;
                }
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_LONG(pos);
}




PHP_METHOD(StdVector, reverse) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            std::reverse(vec->begin(),vec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            std::reverse(vec->begin(),vec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            std::reverse(vec->begin(),vec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            std::reverse(vec->begin(),vec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            std::reverse(vec->begin(),vec->end());
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_TRUE;
}


class ApplyEachCaller {
public:
    zend_fcall_info* fci;
    zend_fcall_info_cache* fci_cache;

    ApplyEachCaller(zend_fcall_info* fci_, zend_fcall_info_cache* fci_cache_) {
        fci = fci_;
        fci_cache = fci_cache_;
    }

    int __call(zval* obj1) const {
        zval **args[1], *retval_ptr = NULL;

        args[0] = &obj1;

        fci->retval_ptr_ptr = &retval_ptr;
        fci->param_count = 1;
        fci->params = args;
        fci->no_separation = 0;

        if (zend_call_function(fci, fci_cache TSRMLS_CC) == SUCCESS) {
            // What should we do here?
            return 1;
        }

        return 0;
    }

    int operator()(zval* obj1) const {
        return this->__call(obj1);
    }
    int operator()(long& val) const {
        zval* obj1;
        MAKE_STD_ZVAL(obj1);
        ZVAL_LONG(obj1, val);

        int ret = this->__call(obj1);

        zval_ptr_dtor(&obj1);

        return ret;
    }
    int operator()(double& val) const {
        zval* obj1;
        MAKE_STD_ZVAL(obj1);
        ZVAL_DOUBLE(obj1, val);

        int ret = this->__call(obj1);

        zval_ptr_dtor(&obj1);

        return ret;
    }

    int operator()(bool val) const {
        zval* obj1;
        MAKE_STD_ZVAL(obj1);
        ZVAL_BOOL(obj1, val);

        int ret = this->__call(obj1);

        zval_ptr_dtor(&obj1);

        return ret;
    }

    int operator()(string& val) const {
        zval* obj1;
        MAKE_STD_ZVAL(obj1);
        ZVAL_STRING(obj1, val.c_str(), 1);

        int ret = this->__call(obj1);

        zval_ptr_dtor(&obj1);

        return ret;
    }
};

// Apply function to all elements in this vector
PHP_METHOD(StdVector, applyEach) {
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            std::for_each (vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            std::for_each (vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            ApplyEachCaller clr(&fci, &fci_cache);
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                clr(*it);
            }
            //std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_TRUE;
}





//Count appearances of value in this vector
PHP_METHOD(StdVector, countValue) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long pos = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntVector *vec = (IntVector*) thisObj->vo;
            pos = std::count(vec->begin(), vec->end(), val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatVector *vec = (FloatVector*) thisObj->vo;
            pos = std::count(vec->begin(), vec->end(), val);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            char *val;
            long val_len = 0;

            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &val, &val_len) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            StringVector *vec = (StringVector*) thisObj->vo;
            pos = std::count(vec->begin(), vec->end(), val);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolVector *vec = (BoolVector*) thisObj->vo;
            pos = std::count(vec->begin(), vec->end(), val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalResource(*it, val)) {
                    pos++;
                }
            }
        }
        break;


        case TYPE_COMPLEX_OBJECT:
        {
            zval *val = NULL;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o!", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalObject(*it, val)) {
                    pos++;
                }
            }
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (compareZvalArray(*it, val)) {
                    pos++;
                }
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_LONG(pos);
}




// fill with value
PHP_METHOD(StdVector, fill) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0, length = 0;
    uLongInt size = 0;

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                long val = 0;
                IntVector *vec = (IntVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|lll", &val, &position, &length) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                double val = 0.00;
                FloatVector *vec = (FloatVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|dll",&val, &position, &length) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                char *val = NULL;
                long val_len = 0;
                StringVector *vec = (StringVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll",&val, &position, &length, &val_len) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                zend_bool val = 0;
                StringVector *vec = (StringVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|bll",&val, &position, &length) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            {
                zval *val = NULL;
                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|rll",&val, &position, &length) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);

                for (auto it = vec->begin()+position; it != vec->begin()+length; ++it) {
                    add_reference_count(*it);
                }
            }
            break;


            case TYPE_COMPLEX_OBJECT:
            {
                zval *val = NULL;
                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                size = vec->size();

                if (thisObj->objCe == NULL) {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|oll",&val, &position, &length) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                        return;
                    }
                } else {
                    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|Oll",&val, &position, &length, thisObj->objCe) == FAILURE) {
                        zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this vector.", 0 TSRMLS_CC);
                        return;
                    }
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);

                if (val != NULL) {
                    for (auto it = vec->begin()+position; it != vec->begin()+length; ++it) {
                        add_reference_count(*it);
                    }
                }
            }
            break;


            case TYPE_COMPLEX_ARRAY:
            {
                zval *val = NULL;
                ZvalVector *vec = (ZvalVector*) thisObj->vo;
                size = vec->size();

                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|all", &val, &position, &length) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }

                if (position < 0 || length < 0) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Start position or length cannot be negative.", 0 TSRMLS_CC);
                    return;
                }

                if (position + length > size) {
                    size = position + length;
                    vec->resize(size);
                }

                if (length == 0) {
                    length = size;
                }

                std::fill(vec->begin()+position, vec->begin()+length, val);

                for (auto it = vec->begin()+position; it != vec->begin()+length; ++it) {
                    add_reference_count(*it);
                }
            }
            break;

            default:
            {
                throw string("Invalid data type");
            }
            break;
        }
    } catch (const std::string& ex) {
        zend_throw_exception(NULL, (char*) ex.c_str(), 0 TSRMLS_CC);
        return;
    } catch (const std::exception& ex) {
        zend_throw_exception(NULL, (char*) ex.what(), 0 TSRMLS_CC);
        return;
    } catch (...) {
        zend_throw_exception(NULL, "Unknown error in StdVector::fill", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}




// Make it unique
PHP_METHOD(StdVector, unique) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end(), compareZvalResource);
        }
        break;

        case TYPE_COMPLEX_OBJECT:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end(), compareZvalObject);
        }
        break;

        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            std::unique(vec->begin(), vec->end(), compareZvalArray);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_TRUE;
}




PHP_METHOD(StdVector, hasNext) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_FALSE;
}


PHP_METHOD(StdVector, hasPrev) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->ptr == 0) {
        RETURN_FALSE;
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_FALSE;
}



PHP_METHOD(StdVector, moveFirst) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    thisObj->ptr = 0;

    RETURN_TRUE;
}

PHP_METHOD(StdVector, moveLast) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_TRUE;
}

PHP_METHOD(StdVector, getPointer) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    long position = thisObj->ptr ? thisObj->ptr - 1 : thisObj->ptr;

    if (hasVectorOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    RETURN_LONG(position);
}

PHP_METHOD(StdVector, getIndex) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    long position = thisObj->ptr ? thisObj->ptr - 1 : thisObj->ptr;

    if (hasVectorOutOfBounds(thisObj, position)) {
        thisObj->ptr = 0;
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    RETURN_LONG(position);
}



PHP_METHOD(StdVector, getValue) {
    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = thisObj->ptr;

    if (position > 0) {
        position--;
    }

    if (hasVectorOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = ((IntVector*) thisObj->vo)->at(position);
            RETURN_LONG(val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = ((FloatVector*) thisObj->vo)->at(position);
            RETURN_DOUBLE(val);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            string val = ((StringVector*) thisObj->vo)->at(position);
            RETURN_STRING((char *) val.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            bool val = ((BoolVector*) thisObj->vo)->at(position);
            RETURN_BOOL(val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            zval *val = (zval *) ((ZvalVector*) thisObj->vo)->at(position);

            RETVAL_ZVAL(val, 1, 0);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}

PHP_METHOD(StdVector, seek) {
    long seekPos = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &seekPos) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();
    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (hasVectorOutOfBounds(thisObj, seekPos)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    thisObj->ptr = seekPos + 1;

    RETURN_TRUE;
}



PHP_METHOD(StdVector, append) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, &vector_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *otherObj = (vector_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not append elements to another type of vector.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector *otherVec = (IntVector*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(vec->end(), otherVec->begin(), otherVec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector *otherVec = (FloatVector*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(vec->end(), otherVec->begin(), otherVec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector *otherVec = (StringVector*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(vec->end(), otherVec->begin(), otherVec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector *otherVec = (BoolVector*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(vec->end(), otherVec->begin(), otherVec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            ZvalVector *otherVec = (ZvalVector*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(vec->end(), otherVec->begin(), otherVec->end());

            for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
                add_reference_count(*it);
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }

    RETURN_TRUE;
}




template<class T>
T* mergeVectors(const T* vec, const T* otherVec) {
    T *merged = new T();

    merged->reserve(vec->size() + otherVec->size());

    std::copy(vec->begin(), vec->end(), merged->begin());
    merged->insert(merged->end(), otherVec->begin(), otherVec->end());

    return merged;
}


PHP_METHOD(StdVector, merge) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, &vector_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *otherObj = (vector_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not merge elements in to another type of vector.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, vector_entry);
    vector_object* resultObject = (vector_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector *otherVec = (IntVector*) otherObj->vo;

            resultObject->vo = mergeVectors<IntVector>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector *otherVec = (FloatVector*) otherObj->vo;

            resultObject->vo = mergeVectors<FloatVector>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector *otherVec = (StringVector*) otherObj->vo;

            resultObject->vo = mergeVectors<StringVector>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector *otherVec = (BoolVector*) otherObj->vo;

            resultObject->vo = mergeVectors<BoolVector>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            ZvalVector *otherVec = (ZvalVector*) otherObj->vo;

            ZvalVector *merged = (ZvalVector*) mergeVectors<ZvalVector>(vec, otherVec);
            resultObject->vo = merged;

            for (auto it = merged->begin(); it != merged->end(); ++it) {
                add_reference_count(*it);
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }
}




template<class T, class X>
T* intersectVectors(const T* vec, const T* otherVec) {
    T *intersect = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0 || otherVecSize == 0) {
        return intersect;
    }

    unordered_map<X, int> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        intersect->reserve(vecSize);
    } else {
        intersect->reserve(otherVecSize);
    }

    for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
        mp[*it] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (mp.count(*it)) {
            intersect->push_back(*it);
        }
    }

    return intersect;
}

template<class T>
T* intersectZvalVectors(const T* vec, const T* otherVec, int type) {
    T *intersect = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0 || otherVecSize == 0) {
        return intersect;
    }

    CompareZvalValue::type = type;
    unordered_map<zval*, int, std::hash<zval*>, CompareZvalValue> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        intersect->reserve(vecSize);
    } else {
        intersect->reserve(otherVecSize);
    }

    for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
        mp[*it] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (mp.count(*it)) {
            intersect->push_back(*it);
        }
    }

    return intersect;
}

PHP_METHOD(StdVector, intersect) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, &vector_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *otherObj = (vector_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not intersect elements in to another type of vector.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, vector_entry);
    vector_object* resultObject = (vector_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector *otherVec = (IntVector*) otherObj->vo;

            resultObject->vo = intersectVectors<IntVector, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector *otherVec = (FloatVector*) otherObj->vo;

            resultObject->vo = intersectVectors<FloatVector, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector *otherVec = (StringVector*) otherObj->vo;

            resultObject->vo = intersectVectors<StringVector, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector *otherVec = (BoolVector*) otherObj->vo;

            resultObject->vo = intersectVectors<BoolVector, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            ZvalVector *otherVec = (ZvalVector*) otherObj->vo;

            ZvalVector *intersect = (ZvalVector*) intersectZvalVectors<ZvalVector>(vec, otherVec, thisObj->type);
            resultObject->vo = intersect;

            for (auto it = intersect->begin(); it != intersect->end(); ++it) {
                add_reference_count(*it);
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }
}






template<class T, class X>
T* diffVectors(const T* vec, const T* otherVec) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->reserve(vecSize);
        std::copy(vec->begin(), vec->end(), diff->begin());
        return diff;
    }

    unordered_map<X, int> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        diff->reserve(vecSize);
    } else {
        diff->reserve(otherVecSize);
    }

    for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
        mp[*it] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (!mp.count(*it)) {
            diff->push_back(*it);
        }
    }

    return diff;
}

template<class T>
T* diffZvalVectors(const T* vec, const T* otherVec, int type) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->reserve(vecSize);
        std::copy(vec->begin(), vec->end(), diff->begin());
        return diff;
    }

    CompareZvalValue::type = type;
    unordered_map<zval*, int, std::hash<zval*>, CompareZvalValue> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        diff->reserve(vecSize);
    } else {
        diff->reserve(otherVecSize);
    }

    for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
        mp[*it] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (!mp.count(*it)) {
            diff->push_back(*it);
        }
    }

    return diff;
}

PHP_METHOD(StdVector, diff) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, &vector_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    vector_object *thisObj = (vector_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *otherObj = (vector_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not diff elements in to another type of vector.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, vector_entry);
    vector_object* resultObject = (vector_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntVector *vec = (IntVector*) thisObj->vo;
            IntVector *otherVec = (IntVector*) otherObj->vo;

            resultObject->vo = diffVectors<IntVector, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector *otherVec = (FloatVector*) otherObj->vo;

            resultObject->vo = diffVectors<FloatVector, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector *otherVec = (StringVector*) otherObj->vo;

            resultObject->vo = diffVectors<StringVector, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector *otherVec = (BoolVector*) otherObj->vo;

            resultObject->vo = diffVectors<BoolVector, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            ZvalVector *otherVec = (ZvalVector*) otherObj->vo;

            ZvalVector *diff = (ZvalVector*) diffZvalVectors<ZvalVector>(vec, otherVec, thisObj->type);
            resultObject->vo = diff;

            for (auto it = diff->begin(); it != diff->end(); ++it) {
                add_reference_count(*it);
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return;
        }
        break;
    }
}