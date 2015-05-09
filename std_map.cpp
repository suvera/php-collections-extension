/**
 *  StdMap class implementation
 */
PHP_METHOD(StdMap, __construct) {
    long type = 0, capacity = 0;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &type, &capacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    thisObj->type = type;

    try {
        switch (type) {
            case TYPE_SCALAR_INT:
            {
                thisObj->vo = new IntStdMap();
                ((IntStdMap*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                thisObj->vo = new FloatStdMap();
                ((FloatStdMap*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                thisObj->vo = new StringStdMap();
                ((StringStdMap*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                thisObj->vo = new BoolStdMap();
                ((BoolStdMap*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                thisObj->vo = new ZvalStdMap();
                ((ZvalStdMap*) thisObj->vo)->reserve(capacity);
            }
            break;

            default:
            {
                char buffer[100];
                sprintf(buffer, "Invalid data type %ld", type);
                throw string(buffer);
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
        zend_throw_exception(NULL, "Unknown error in StdMap::__construct", 0 TSRMLS_CC);
        return;
    }
}


PHP_METHOD(StdMap, size)
{
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long count = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            count = ((IntStdMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            count = ((FloatStdMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            count = ((StringStdMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            count = ((BoolStdMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            count = ((ZvalStdMap*) thisObj->vo)->size();
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





PHP_METHOD(StdMap, reserve) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long newCapacity = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &newCapacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdMap*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdMap*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdMap*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdMap*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ((ZvalStdMap*) thisObj->vo)->reserve(newCapacity);
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
        zend_throw_exception(NULL, "Unknown error in StdMap::reserve", 0 TSRMLS_CC);
        return;
    }
}




PHP_METHOD(StdMap, at) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;
    char *key;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &position) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                long val = ((IntStdMap*) thisObj->vo)->at(key);
                RETURN_LONG(val);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                double val = ((FloatStdMap*) thisObj->vo)->at(key);
                RETURN_DOUBLE(val);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                string val = ((StringStdMap*) thisObj->vo)->at(key);
                RETURN_STRING((char *) val.c_str(), 1);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                bool val = ((BoolStdMap*) thisObj->vo)->at(key);
                RETURN_BOOL(val);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                zval *val = (zval *) ((ZvalStdMap*) thisObj->vo)->at(key);

                RETVAL_ZVAL(val, 1, 0);
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
        zend_throw_exception(NULL, "Unknown error in StdMap::at", 0 TSRMLS_CC);
        return;
    }
}





PHP_METHOD(StdMap, hasKey) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;
    char *key;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &position) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zend_bool keyExists = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            keyExists = ((IntStdMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            keyExists = ((FloatStdMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            keyExists = ((StringStdMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            keyExists = ((BoolStdMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            keyExists = ((ZvalStdMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }

    RETURN_FALSE;
}





PHP_METHOD(StdMap, push) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    char *key;
    long keyLength = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            (*vec)[key] = val;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sd", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            (*vec)[key] = val;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            char *val;
            long val_len = 0;

            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &keyLength, &val, &val_len) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            (*vec)[key] = val;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sb", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            (*vec)[key] = val;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sr", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            if (vec->count(key)) {
                delete_reference_count(vec->at(key));
            }
            (*vec)[key] = val;

            add_reference_count(val);
        }
        break;


        case TYPE_COMPLEX_OBJECT:
        {
            zval *val = NULL;

            if (thisObj->objCe == NULL) {
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "so!", &key, &keyLength, &val) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                    return;
                }
            } else {
                if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sO!", &key, &keyLength, &val, thisObj->objCe) == FAILURE) {
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this vector.", 0 TSRMLS_CC);
                    return;
                }
            }

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            if (vec->count(key)) {
                delete_reference_count(vec->at(key));
            }

            if (thisObj->objCe == NULL && val != NULL) {
                thisObj->objCe = Z_OBJCE_P(val);
            }

            (*vec)[key] = val;
            add_reference_count(val);
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            if (vec->count(key)) {
                delete_reference_count(vec->at(key));
            }
            (*vec)[key] = val;

            add_reference_count(val);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }

    RETURN_TRUE;
}






/**
 * Only Applicable to unordered_map<string, Object>
 */
PHP_METHOD(StdMap, getClass) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->objCe == NULL) {
        RETURN_NULL();
    } else {
        RETURN_STRING((char *) thisObj->objCe->name, 1);
    }
}





PHP_METHOD(StdMap, erase) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0, length = 0;
    char *key;
    long erased = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &length) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

            zval *val = vec->at(key);
            delete_reference_count(val);

            erased = vec->erase(key);
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }

    RETURN_LONG(erased);
}





PHP_METHOD(StdMap, clear) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

                //Z_DELREF_P(new_var);
                for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                    delete_reference_count(it->second);
                }

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
        zend_throw_exception(NULL, "Unknown error in StdMap::clear", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}





static void findValue(INTERNAL_FUNCTION_PARAMETERS, int retBool) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long pos = -1;
    char *key = NULL;
    zend_bool found = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntStdMap *vec = (IntStdMap*) thisObj->vo;

            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (it->second == val) {
                    key = (char *) it->first.c_str();
                    found = 1;
                    break;
                }
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0.00;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (it->second == val) {
                    found = 1;
                    key = (char *) it->first.c_str();
                    break;
                }
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

            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (it->second.compare(val) == 0) {
                    found = 1;
                    key = (char *) it->first.c_str();
                    break;
                }
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

            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (it->second == val) {
                    found = 1;
                    key = (char *) it->first.c_str();
                    break;
                }
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

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if (Z_LVAL_P(it->second) == Z_LVAL_P(val)) {
                    found = 1;
                    key = (char *) it->first.c_str();
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

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            if (val != NULL) {
                for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                    if (Z_OBJ_HT_P(it->second) == Z_OBJ_HT_P(val) && (Z_OBJ_HANDLE_P(it->second) == Z_OBJ_HANDLE_P(val))) {
                        found = 1;
                        key = (char *) it->first.c_str();
                        break;
                    }
                }
            } else {
                for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                    if (it->second == NULL) {
                        found = 1;
                        key = (char *) it->first.c_str();
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

            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

            for (auto it = vec->cbegin(); it != vec->cend(); ++it) {
                if ((Z_ARRVAL_P(it->second) == Z_ARRVAL_P(val)) ||
                    zend_hash_compare(Z_ARRVAL_P(it->second), Z_ARRVAL_P(val), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC)==0) {
                    found = 1;
                    key = (char *) it->first.c_str();
                    break;
                }
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }

    if (retBool) {
        RETURN_BOOL(found);
    } else if (key == NULL) {
        RETURN_NULL();
    } else {
        RETURN_STRING(key, 1);
    }
}

// search for a Value
PHP_METHOD(StdMap, search) {
    findValue(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}

PHP_METHOD(StdMap, hasValue) {
    findValue(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}






/**
 * return keys as StdVector
 */
PHP_METHOD(StdMap, keys) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *newObject;

    object_init_ex(return_value, vector_entry);
    newObject = (map_object *) zend_object_store_get_object(return_value TSRMLS_CC);

    newObject->type = TYPE_SCALAR_STRING;
    newObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        default:
        {
            map_object_free_storage(newObject TSRMLS_CC);
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}

/**
 * return values as StdVector
 */
PHP_METHOD(StdMap, values) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *newObject;

    object_init_ex(return_value, vector_entry);
    newObject = (map_object *) zend_object_store_get_object(return_value TSRMLS_CC);

    newObject->type = thisObj->type;
    newObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            IntVector *v = new IntVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            FloatVector *v = new FloatVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            BoolVector *v = new BoolVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            ZvalVector *v = new ZvalVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(it->second);
                add_reference_count(it->second);
            }

            newObject->vo = v;
        }
        break;

        default:
        {
            map_object_free_storage(newObject TSRMLS_CC);
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}







/** ********************************************************************
 * #####################################################################
 *  Iterator
 *
 */
static bool hasStdMapOutOfBounds(const map_object *thisObj, const long &position) {

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
            return (position < 0 || position >= ((IntStdMap*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_FLOAT:
            return (position < 0 || position >= ((FloatStdMap*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_STRING:
            return (position < 0 || position >= ((StringStdMap*) thisObj->vo)->size());
        break;

        case TYPE_SCALAR_BOOL:
            return (position < 0 || position >= ((BoolStdMap*) thisObj->vo)->size());
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
            return (position < 0 || position >= ((ZvalStdMap*) thisObj->vo)->size());
        break;
    }

    return false;
}

PHP_METHOD(StdMap, hasNext) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;

            if (thisObj->ptr < vec->size()) {
                thisObj->ptr++;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;

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
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

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


PHP_METHOD(StdMap, hasPrev) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->ptr == 0) {
        RETURN_FALSE;
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;

            if (thisObj->ptr > 0) {
                thisObj->ptr--;
                RETURN_TRUE;
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;

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
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

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



PHP_METHOD(StdMap, moveFirst) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    thisObj->ptr = 0;

    RETURN_TRUE;
}

PHP_METHOD(StdMap, moveLast) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;

            thisObj->ptr = vec->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

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

PHP_METHOD(StdMap, getPointer) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    long position = thisObj->ptr ? thisObj->ptr - 1 : thisObj->ptr;

    if (hasStdMapOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    RETURN_LONG(position);
}

PHP_METHOD(StdMap, getKey) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    long position = thisObj->ptr ? thisObj->ptr - 1 : thisObj->ptr;

    if (hasStdMapOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *)  it->first.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *)  it->first.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *)  it->first.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *)  it->first.c_str(), 1);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *)  it->first.c_str(), 1);
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



PHP_METHOD(StdMap, getValue) {
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = thisObj->ptr;

    if (position > 0) {
        position--;
    }

    if (hasStdMapOutOfBounds(thisObj, position)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_LONG(it->second);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_DOUBLE(it->second);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_STRING((char *) it->second.c_str(), 1);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            RETURN_BOOL(it->second);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            auto it = vec->cbegin();
            std::advance(it, position);
            zval *val = (zval*) it->second;

            if (val == NULL) {
                RETURN_NULL();
            } else {
                RETVAL_ZVAL(val, 1, 0);
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

PHP_METHOD(StdMap, seek) {
    long seekPos = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &seekPos) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (hasStdMapOutOfBounds(thisObj, seekPos)) {
        zend_throw_exception(NULL, "IndexOutOfBoundsException, Internal Position is not in the vector.", 0 TSRMLS_CC);
        return;
    }

    thisObj->ptr = seekPos + 1;

    RETURN_TRUE;
}
