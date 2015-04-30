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

            Z_ADDREF_P(val);
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

                Z_ADDREF_P(val);
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

            Z_ADDREF_P(val);
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

                Z_ADDREF_P(val);
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

                    Z_ADDREF_P(val);
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

                Z_ADDREF_P(val);
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

                Z_ADDREF_P(val);
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

                    Z_ADDREF_P(val);
                } else {
                    vec->insert(vec->begin()+position, NULL);
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
                vec->insert(vec->begin()+position, val);

                Z_ADDREF_P(val);
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
    void*** tsrmls_dc;

    ObjectSorter(zend_fcall_info* fci_, zend_fcall_info_cache* fci_cache_, void*** tsrmls_dc_) {
        fci = fci_;
        fci_cache = fci_cache_;
        tsrmls_dc = tsrmls_dc_;
    }

    int operator()(zval* obj1, zval* obj2) const {
        zval **args[2], *retval_ptr = NULL;

        args[0] = &obj1;
        args[1] = &obj2;

        fci->retval_ptr_ptr = &retval_ptr;
        fci->param_count = 2;
        fci->params = args;
        fci->no_separation = 0;

        if (zend_call_function(fci, fci_cache, tsrmls_dc) == SUCCESS) {
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
                std::sort(vec->begin(), vec->end(), ObjectSorter(&fci, &fci_cache TSRMLS_CC));
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
                if (Z_LVAL_P(*it) == Z_LVAL_P(val)) {
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
            if (val != NULL) {
                for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                    if (Z_OBJ_HT_P(*it) == Z_OBJ_HT_P(val) && (Z_OBJ_HANDLE_P(*it) == Z_OBJ_HANDLE_P(val))) {
                        pos = it - vec->begin();
                        break;
                    }
                }
            } else {
                for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                    if (*it == NULL) {
                        pos = it - vec->begin();
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
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if ((Z_ARRVAL_P(*it) == Z_ARRVAL_P(val)) ||
                    zend_hash_compare(Z_ARRVAL_P(*it), Z_ARRVAL_P(val), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC)==0) {

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



// TODO: implement this method
PHP_METHOD(StdVector, applyEach) {}


// TODO: implement this method
PHP_METHOD(StdVector, countValue) {}


// TODO: implement this method
PHP_METHOD(StdVector, fill) {}


// TODO: implement this method
PHP_METHOD(StdVector, unique) {}


// TODO: implement this method
PHP_METHOD(StdVector, replaceIf) {}


// TODO: implement this method
PHP_METHOD(StdVector, removeIf) {}



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
                if (*it != NULL) {
                    Z_ADDREF_P(*it);
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

    RETURN_TRUE;
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

            IntVector *merged = new IntVector();
            merged->reserve(vec->size() + otherVec->size());
            std::merge(vec->begin(), vec->end(), otherVec->begin(), otherVec->end(), merged->begin());
            resultObject->vo = merged;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatVector *vec = (FloatVector*) thisObj->vo;
            FloatVector *otherVec = (FloatVector*) otherObj->vo;

            FloatVector *merged = new FloatVector();
            merged->reserve(vec->size() + otherVec->size());
            std::merge(vec->begin(), vec->end(), otherVec->begin(), otherVec->end(), merged->begin());
            resultObject->vo = merged;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringVector *vec = (StringVector*) thisObj->vo;
            StringVector *otherVec = (StringVector*) otherObj->vo;

            StringVector *merged = new StringVector();
            merged->reserve(vec->size() + otherVec->size());
            std::merge(vec->begin(), vec->end(), otherVec->begin(), otherVec->end(), merged->begin());
            resultObject->vo = merged;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolVector *vec = (BoolVector*) thisObj->vo;
            BoolVector *otherVec = (BoolVector*) otherObj->vo;

            BoolVector *merged = new BoolVector();
            merged->reserve(vec->size() + otherVec->size());
            std::merge(vec->begin(), vec->end(), otherVec->begin(), otherVec->end(), merged->begin());
            resultObject->vo = merged;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalVector *vec = (ZvalVector*) thisObj->vo;
            ZvalVector *otherVec = (ZvalVector*) otherObj->vo;

            ZvalVector *merged = new ZvalVector();
            merged->reserve(vec->size() + otherVec->size());
            std::merge(vec->begin(), vec->end(), otherVec->begin(), otherVec->end(), merged->begin());
            resultObject->vo = merged;

            for (auto it = merged->begin(); it != merged->end(); ++it) {
                if (*it != NULL) {
                    Z_ADDREF_P(*it);
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
}

PHP_METHOD(StdVector, intersect) {}

PHP_METHOD(StdVector, diff) {}