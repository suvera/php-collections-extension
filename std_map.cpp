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
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this map.", 0 TSRMLS_CC);
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
 * return keys as StdMap
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
 * return values as StdMap
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





// Apply function to all elements in this map
PHP_METHOD(StdMap, applyEach) {
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }
    zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            ApplyEachCaller clr(&fci, &fci_cache);
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                clr(*it);
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
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







// Take other StdMap as input append to elements into this
PHP_METHOD(StdMap, append) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *otherObj = (map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not append elements to another type of map.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            IntStdMap *otherVec = (IntStdMap*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            FloatStdMap *otherVec = (FloatStdMap*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringStdMap *otherVec = (StringStdMap*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            BoolStdMap *otherVec = (BoolStdMap*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            ZvalStdMap *otherVec = (ZvalStdMap*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());

            for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
                if (!vec->count(it->first)) {
                    vec->insert(*it);
                    add_reference_count(it->second);
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

// Take other StdMap as input and return StdMap
template<class T>
T* mergeStdMaps(const T* vec, const T* otherVec) {
    T *merged = new T();

    merged->reserve(vec->size() + otherVec->size());

    merged->insert(vec->begin(), vec->end());
    merged->insert(otherVec->begin(), otherVec->end());

    return merged;
}


PHP_METHOD(StdMap, merge) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *otherObj = (map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not merge elements in to another type of map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, map_entry);
    map_object* resultObject = (map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            IntStdMap *otherVec = (IntStdMap*) otherObj->vo;

            resultObject->vo = mergeStdMaps<IntStdMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            FloatStdMap *otherVec = (FloatStdMap*) otherObj->vo;

            resultObject->vo = mergeStdMaps<FloatStdMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringStdMap *otherVec = (StringStdMap*) otherObj->vo;

            resultObject->vo = mergeStdMaps<StringStdMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            BoolStdMap *otherVec = (BoolStdMap*) otherObj->vo;

            resultObject->vo = mergeStdMaps<BoolStdMap>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            ZvalStdMap *otherVec = (ZvalStdMap*) otherObj->vo;

            ZvalStdMap *merged = (ZvalStdMap*) mergeStdMaps<ZvalStdMap>(vec, otherVec);
            resultObject->vo = merged;

            for (auto it = merged->begin(); it != merged->end(); ++it) {
                add_reference_count(it->second);
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
T* intersectStdMaps(const T* vec, const T* otherVec) {
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
        mp[it->second] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (mp.count(it->second)) {
            intersect->insert(*it);
        }
    }

    return intersect;
}

template<class T>
T* intersectZvalStdMaps(const T* vec, const T* otherVec, int type) {
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
        mp[it->second] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (mp.count(it->second)) {
            intersect->insert(*it);
        }
    }

    return intersect;
}

PHP_METHOD(StdMap, intersect) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *otherObj = (map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not intersect elements in to another type of map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, map_entry);
    map_object* resultObject = (map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            IntStdMap *otherVec = (IntStdMap*) otherObj->vo;

            resultObject->vo = intersectStdMaps<IntStdMap, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            FloatStdMap *otherVec = (FloatStdMap*) otherObj->vo;

            resultObject->vo = intersectStdMaps<FloatStdMap, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringStdMap *otherVec = (StringStdMap*) otherObj->vo;

            resultObject->vo = intersectStdMaps<StringStdMap, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            BoolStdMap *otherVec = (BoolStdMap*) otherObj->vo;

            resultObject->vo = intersectStdMaps<BoolStdMap, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            ZvalStdMap *otherVec = (ZvalStdMap*) otherObj->vo;

            ZvalStdMap *intersect = (ZvalStdMap*) intersectZvalStdMaps<ZvalStdMap>(vec, otherVec, thisObj->type);
            resultObject->vo = intersect;

            for (auto it = intersect->begin(); it != intersect->end(); ++it) {
                add_reference_count(it->second);
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
T* diffStdMaps(const T* vec, const T* otherVec) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->reserve(vecSize);
        diff->insert(vec->begin(), vec->end());
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
        mp[it->second] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (!mp.count(it->second)) {
            diff->insert(*it);
        }
    }

    return diff;
}

template<class T>
T* diffZvalStdMaps(const T* vec, const T* otherVec, int type) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->reserve(vecSize);
        diff->insert(vec->begin(), vec->end());
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
        mp[it->second] = 1;
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (!mp.count(it->second)) {
            diff->insert(*it);
        }
    }

    return diff;
}

PHP_METHOD(StdMap, diff) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);
    map_object *otherObj = (map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not diff elements in to another type of map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, map_entry);
    map_object* resultObject = (map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;
            IntStdMap *otherVec = (IntStdMap*) otherObj->vo;

            resultObject->vo = diffStdMaps<IntStdMap, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
            FloatStdMap *otherVec = (FloatStdMap*) otherObj->vo;

            resultObject->vo = diffStdMaps<FloatStdMap, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;
            StringStdMap *otherVec = (StringStdMap*) otherObj->vo;

            resultObject->vo = diffStdMaps<StringStdMap, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
            BoolStdMap *otherVec = (BoolStdMap*) otherObj->vo;

            resultObject->vo = diffStdMaps<BoolStdMap, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
            ZvalStdMap *otherVec = (ZvalStdMap*) otherObj->vo;

            ZvalStdMap *diff = (ZvalStdMap*) diffZvalStdMaps<ZvalStdMap>(vec, otherVec, thisObj->type);
            resultObject->vo = diff;

            for (auto it = diff->begin(); it != diff->end(); ++it) {
                add_reference_count(it->second);
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






/**
 * To Array
 *
 */
static int toArray(map_object *thisObj, zval *arr TSRMLS_DC) {
    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdMap *vec = (IntStdMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_long(arr, it->first.c_str(), it->second);
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdMap *vec = (FloatStdMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_double(arr, it->first.c_str(), it->second);
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdMap *vec = (StringStdMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_stringl(arr, it->first.c_str(), (char *) it->second.c_str(), it->second.length(), 1);
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdMap *vec = (BoolStdMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_bool(arr, it->first.c_str(), it->second);
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_zval(arr, it->first.c_str(), it->second);
                add_reference_count(it->second);
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
            return 0;
        }
        break;
    }

    return 1;
}


/**
 * serialize
 */
PHP_METHOD(StdMap, serialize) {
    zval *val, *wrapper;
	php_serialize_data_t var_hash;
	smart_str buf = {0};
    zval *object = getThis();

    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

    MAKE_STD_ZVAL(wrapper);
    MAKE_STD_ZVAL(val);

    array_init(wrapper);
    add_assoc_long(wrapper, "type", thisObj->type);

    toArray(thisObj, val TSRMLS_CC);

    add_assoc_zval(wrapper, "data", val);

	Z_TYPE_P(return_value) = IS_STRING;
	Z_STRVAL_P(return_value) = NULL;
	Z_STRLEN_P(return_value) = 0;

	PHP_VAR_SERIALIZE_INIT(var_hash);
	php_var_serialize(&buf, &val, &var_hash TSRMLS_CC);
	PHP_VAR_SERIALIZE_DESTROY(var_hash);

    zval_ptr_dtor(&val);
    zval_ptr_dtor(&wrapper);

	if (EG(exception)) {
		smart_str_free(&buf);
		RETURN_FALSE;
	}

	if (buf.c) {
		RETURN_STRINGL(buf.c, buf.len, 0);
	} else {
		RETURN_NULL();
	}
}


/**
 * unserialize
 */
PHP_METHOD(StdMap, unserialize) {
    char *buf = NULL;
    int buf_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &buf, &buf_len) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

	const unsigned char *p;
	php_unserialize_data_t var_hash;

	if (buf_len == 0) {
		RETURN_FALSE;
	}

	zval *object = getThis();
    map_object *thisObj = (map_object *) zend_object_store_get_object(object TSRMLS_CC);

	zval *arr;

	MAKE_STD_ZVAL(arr);

	p = (const unsigned char*) buf;
	PHP_VAR_UNSERIALIZE_INIT(var_hash);

	if (!php_var_unserialize(&arr, &p, p + buf_len, &var_hash TSRMLS_CC)) {
		PHP_VAR_UNSERIALIZE_DESTROY(var_hash);
		zval_dtor(arr);

		if (!EG(exception)) {
		    char buffer[512];
		    sprintf(buffer, "Error at offset %ld of %d bytes", (long)((char*)p - buf), buf_len);
		    zend_throw_exception(NULL, buffer, 0 TSRMLS_CC);
		    return;
		}

		RETURN_FALSE;
	}

	PHP_VAR_UNSERIALIZE_DESTROY(var_hash);

    zval** zv_type = NULL;
	if (zend_hash_find(Z_ARRVAL_P(arr), "type", sizeof("type"), (void **) &zv_type) != SUCCESS) {
        //zval_ptr_dtor(zv_type);
        zval_dtor(arr);
        zend_throw_exception(NULL, "Invalid serialized data, could not find 'type'.", 0 TSRMLS_CC);
        return;
	}

	zval** zv_data = NULL;
    if (zend_hash_find(Z_ARRVAL_P(arr), "data", sizeof("data"), (void **) &zv_data) != SUCCESS) {
        //zval_ptr_dtor(zv_data);
        zval_dtor(arr);
        zend_throw_exception(NULL, "Invalid serialized data, could not find 'type'.", 0 TSRMLS_CC);
        return;
    }

    HashPosition position;
    zval **data = NULL;
    int c = 0;

    for (zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(*zv_data), &position);
         zend_hash_get_current_data_ex(Z_ARRVAL_P(*zv_data), (void**) &data, &position) == SUCCESS;
         zend_hash_move_forward_ex(Z_ARRVAL_P(*zv_data), &position)) {

        /* by now we have data set and can use Z_ macros for accessing type and variable data */

        char *key = NULL;
        uint  klen;
        ulong index;

        zend_hash_get_current_key_ex(Z_ARRVAL_P(*zv_data), &key, &klen, &index, 0, &position);

        // HASH_KEY_IS_STRING : the key is a string, key and klen will be set */
        // ELSE : we assume the key to be long, index will be set */

        switch (Z_LVAL_P(*zv_type)) {
            case TYPE_SCALAR_INT:
            {
                IntStdMap *vec = (IntStdMap*) thisObj->vo;
                if (c == 0) {
                    vec->reserve(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                }
                (*vec)[key] = Z_LVAL_P(*data);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                FloatStdMap *vec = (FloatStdMap*) thisObj->vo;
                if (c == 0) {
                    vec->reserve(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                }
                (*vec)[key] = Z_DVAL_P(*data);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                StringStdMap *vec = (StringStdMap*) thisObj->vo;
                if (c == 0) {
                    vec->reserve(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                }
                (*vec)[key] = Z_STRLEN_P(*data);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                BoolStdMap *vec = (BoolStdMap*) thisObj->vo;
                if (c == 0) {
                    vec->reserve(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                }
                (*vec)[key] = Z_BVAL_P(*data);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdMap *vec = (ZvalStdMap*) thisObj->vo;
                if (c == 0) {
                    vec->reserve(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                }
                (*vec)[key] = *data;
                //add_reference_count(*data);
            }
            break;

            default:
            {
                zend_throw_exception(NULL, "Invalid data type, could not unserialize", 0 TSRMLS_CC);
                return;
            }
            break;
        }

        c = 1;
    }

    zval_ptr_dtor(zv_type);
    zval_ptr_dtor(zv_data);
	zval_dtor(arr);
}

