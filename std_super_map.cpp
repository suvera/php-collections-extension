#if defined(HAVE_GOOGLE_LOCAL) || defined(HAVE_GOOGLE_LOCAL)

/**
 *  StdSuperMap class implementation
 */
PHP_METHOD(StdSuperMap, __construct) {
    long type = 0, capacity = 0;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &type, &capacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

    thisObj->type = type;

    try {
        switch (type) {
            case TYPE_SCALAR_INT:
            {
                thisObj->vo = new IntStdSuperMap();
                ((IntStdSuperMap*) thisObj->vo)->set_empty_key(SUPER_MAP_EMPTY_KEY);
                ((IntStdSuperMap*) thisObj->vo)->set_deleted_key(SUPER_MAP_DELETED_KEY);
                ((IntStdSuperMap*) thisObj->vo)->resize(capacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                thisObj->vo = new FloatStdSuperMap();
                ((FloatStdSuperMap*) thisObj->vo)->set_empty_key(SUPER_MAP_EMPTY_KEY);
                ((FloatStdSuperMap*) thisObj->vo)->set_deleted_key(SUPER_MAP_DELETED_KEY);
                ((FloatStdSuperMap*) thisObj->vo)->resize(capacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                thisObj->vo = new StringStdSuperMap();
                ((StringStdSuperMap*) thisObj->vo)->set_empty_key(SUPER_MAP_EMPTY_KEY);
                ((StringStdSuperMap*) thisObj->vo)->set_deleted_key(SUPER_MAP_DELETED_KEY);
                ((StringStdSuperMap*) thisObj->vo)->resize(capacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                thisObj->vo = new BoolStdSuperMap();
                ((BoolStdSuperMap*) thisObj->vo)->set_empty_key(SUPER_MAP_EMPTY_KEY);
                ((BoolStdSuperMap*) thisObj->vo)->set_deleted_key(SUPER_MAP_DELETED_KEY);
                ((BoolStdSuperMap*) thisObj->vo)->resize(capacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                thisObj->vo = new ZvalStdSuperMap();
                ((ZvalStdSuperMap*) thisObj->vo)->set_empty_key(SUPER_MAP_EMPTY_KEY);
                ((ZvalStdSuperMap*) thisObj->vo)->set_deleted_key(SUPER_MAP_DELETED_KEY);
                ((ZvalStdSuperMap*) thisObj->vo)->resize(capacity);
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
        zend_throw_exception(NULL, "Unknown error in StdSuperMap::__construct", 0 TSRMLS_CC);
        return;
    }
}


PHP_METHOD(StdSuperMap, size)
{
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long count = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            count = ((IntStdSuperMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            count = ((FloatStdSuperMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            count = ((StringStdSuperMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            count = ((BoolStdSuperMap*) thisObj->vo)->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            count = ((ZvalStdSuperMap*) thisObj->vo)->size();
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





PHP_METHOD(StdSuperMap, reserve) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long newCapacity = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &newCapacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdSuperMap*) thisObj->vo)->resize(newCapacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdSuperMap*) thisObj->vo)->resize(newCapacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdSuperMap*) thisObj->vo)->resize(newCapacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdSuperMap*) thisObj->vo)->resize(newCapacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ((ZvalStdSuperMap*) thisObj->vo)->resize(newCapacity);
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
        zend_throw_exception(NULL, "Unknown error in StdSuperMap::reserve", 0 TSRMLS_CC);
        return;
    }
}




PHP_METHOD(StdSuperMap, at) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    long position = 0;
    const char *key;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &position) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = ((IntStdSuperMap*) thisObj->vo);
            if (vec->count(key)) {
                long val = (*vec)[key];
                RETURN_LONG(val);
                return;
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = ((FloatStdSuperMap*) thisObj->vo);
            if (vec->count(key)) {
                double val = (*vec)[key];
                RETURN_DOUBLE(val);
                return;
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = ((StringStdSuperMap*) thisObj->vo);
            if (vec->count(key)) {
                string val = (*vec)[key];
                RETURN_STRING((char *) val.c_str(), 1);
                return;
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = ((BoolStdSuperMap*) thisObj->vo);
            if (vec->count(key)) {
                bool val = (*vec)[key];
                RETURN_BOOL(val);
                return;
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = ((ZvalStdSuperMap*) thisObj->vo);
            if (vec->count(key)) {
                zval *val = (*vec)[key];
                RETVAL_ZVAL(val, 1, 0);
                return;
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

    zend_throw_exception(NULL, "Specified key could not found in the map", 0 TSRMLS_CC);
}





PHP_METHOD(StdSuperMap, hasKey) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
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
            keyExists = ((IntStdSuperMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
            return;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            keyExists = ((FloatStdSuperMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
            return;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            keyExists = ((StringStdSuperMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
            return;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            keyExists = ((BoolStdSuperMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
            return;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            keyExists = ((ZvalStdSuperMap*) thisObj->vo)->count(key);
            RETURN_BOOL(keyExists);
            return;
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





PHP_METHOD(StdSuperMap, push) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
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

            char *KeyCpy = estrndup(key, keyLength);

            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            (*vec)[KeyCpy] = val;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sd", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            char *KeyCpy = estrndup(key, keyLength);

            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            (*vec)[KeyCpy] = val;
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

            char *KeyCpy = estrndup(key, keyLength);

            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            (*vec)[KeyCpy] = val;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sb", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            char *KeyCpy = estrndup(key, keyLength);

            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            (*vec)[KeyCpy] = val;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sr", &key, &keyLength, &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            char *KeyCpy = estrndup(key, keyLength);

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            if (vec->count(KeyCpy)) {
                delete_reference_count((*vec)[KeyCpy]);
            }
            (*vec)[KeyCpy] = val;

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
                    zend_throw_exception(NULL, "Invalid input parameters to the method, Could not add other objects into this super_map.", 0 TSRMLS_CC);
                    return;
                }
            }

            char *KeyCpy = estrndup(key, keyLength);

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            if (vec->count(KeyCpy)) {
                delete_reference_count((*vec)[KeyCpy]);
            }

            if (thisObj->objCe == NULL && val != NULL) {
                thisObj->objCe = Z_OBJCE_P(val);
            }

            (*vec)[KeyCpy] = val;
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

            char *KeyCpy = estrndup(key, keyLength);

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            if (vec->count(KeyCpy)) {
                delete_reference_count((*vec)[KeyCpy]);
            }
            (*vec)[KeyCpy] = val;

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
 * Only Applicable to container<string, Object>
 */
PHP_METHOD(StdSuperMap, getClass) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->objCe == NULL) {
        RETURN_NULL();
    } else {
        RETURN_STRING((char *) thisObj->objCe->name, 1);
    }
}





PHP_METHOD(StdSuperMap, erase) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
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
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            erased = vec->erase(key);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;

            zval *val = (*vec)[key];
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





PHP_METHOD(StdSuperMap, clear) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdSuperMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdSuperMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdSuperMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdSuperMap*) thisObj->vo)->clear();

            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;

                //Z_DELREF_P(new_var);
                for (auto it = vec->begin(); it != vec->end(); ++it ) {
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
        zend_throw_exception(NULL, "Unknown error in StdSuperMap::clear", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}





static void findSuperValue(INTERNAL_FUNCTION_PARAMETERS, int retBool) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
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

            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;

            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if (it->second == val) {
                    key = (char *) it->first;
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

            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if (it->second == val) {
                    found = 1;
                    key = (char *) it->first;
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

            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if (it->second.compare(val) == 0) {
                    found = 1;
                    key = (char *) it->first;
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

            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if (it->second == val) {
                    found = 1;
                    key = (char *) it->first;
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

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if (Z_LVAL_P(it->second) == Z_LVAL_P(val)) {
                    found = 1;
                    key = (char *) it->first;
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

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            if (val != NULL) {
                for (auto it = vec->begin(); it != vec->end(); ++it) {
                    if (Z_OBJ_HT_P(it->second) == Z_OBJ_HT_P(val) && (Z_OBJ_HANDLE_P(it->second) == Z_OBJ_HANDLE_P(val))) {
                        found = 1;
                        key = (char *) it->first;
                        break;
                    }
                }
            } else {
                for (auto it = vec->begin(); it != vec->end(); ++it) {
                    if (it->second == NULL) {
                        found = 1;
                        key = (char *) it->first;
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

            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;

            for (auto it = vec->begin(); it != vec->end(); ++it) {
                if ((Z_ARRVAL_P(it->second) == Z_ARRVAL_P(val)) ||
                    zend_hash_compare(Z_ARRVAL_P(it->second), Z_ARRVAL_P(val), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC)==0) {
                    found = 1;
                    key = (char *) it->first;
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
PHP_METHOD(StdSuperMap, search) {
    findSuperValue(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}

PHP_METHOD(StdSuperMap, hasValue) {
    findSuperValue(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}






/**
 * return keys as StdSuperMap
 */
PHP_METHOD(StdSuperMap, keys) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *newObject;

    object_init_ex(return_value, vector_entry);
    newObject = (vector_object *) zend_object_store_get_object(return_value TSRMLS_CC);

    newObject->type = TYPE_SCALAR_STRING;
    newObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->first);
            }

            newObject->vo = v;
        }
        break;

        default:
        {
            vector_object_free_storage(newObject TSRMLS_CC);
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}

/**
 * return values as StdVector
 */
PHP_METHOD(StdSuperMap, values) {
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    vector_object *newObject;

    object_init_ex(return_value, vector_entry);
    newObject = (vector_object *) zend_object_store_get_object(return_value TSRMLS_CC);

    newObject->type = thisObj->type;
    newObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            IntVector *v = new IntVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            FloatVector *v = new FloatVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            BoolVector *v = new BoolVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->second);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            ZvalVector *v = new ZvalVector();

            v->reserve(vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it ) {
                v->push_back(it->second);
                add_reference_count(it->second);
            }

            newObject->vo = v;
        }
        break;

        default:
        {
            vector_object_free_storage(newObject TSRMLS_CC);
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}





// Apply function to all elements in this super_map
PHP_METHOD(StdSuperMap, applyEach) {
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }
    zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
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
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
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







// Take other StdSuperMap as input append to elements into this
PHP_METHOD(StdSuperMap, append) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, super_map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    super_map_object *otherObj = (super_map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not append elements to another type of super_map.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            IntStdSuperMap *otherVec = (IntStdSuperMap*) otherObj->vo;
            vec->resize(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            FloatStdSuperMap *otherVec = (FloatStdSuperMap*) otherObj->vo;
            vec->resize(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringStdSuperMap *otherVec = (StringStdSuperMap*) otherObj->vo;
            vec->resize(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            BoolStdSuperMap *otherVec = (BoolStdSuperMap*) otherObj->vo;
            vec->resize(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            ZvalStdSuperMap *otherVec = (ZvalStdSuperMap*) otherObj->vo;
            vec->resize(vec->size() + otherVec->size());

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

// Take other StdSuperMap as input and return StdSuperMap
template<class T>
T* mergeStdSuperMaps(const T* vec, const T* otherVec) {
    T *merged = new T();

    merged->resize(vec->size() + otherVec->size());

    merged->insert(vec->begin(), vec->end());
    merged->insert(otherVec->begin(), otherVec->end());

    return merged;
}


PHP_METHOD(StdSuperMap, merge) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, super_map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    super_map_object *otherObj = (super_map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not merge elements in to another type of super_map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, super_map_entry);
    super_map_object* resultObject = (super_map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            IntStdSuperMap *otherVec = (IntStdSuperMap*) otherObj->vo;

            resultObject->vo = mergeStdSuperMaps<IntStdSuperMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            FloatStdSuperMap *otherVec = (FloatStdSuperMap*) otherObj->vo;

            resultObject->vo = mergeStdSuperMaps<FloatStdSuperMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringStdSuperMap *otherVec = (StringStdSuperMap*) otherObj->vo;

            resultObject->vo = mergeStdSuperMaps<StringStdSuperMap>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            BoolStdSuperMap *otherVec = (BoolStdSuperMap*) otherObj->vo;

            resultObject->vo = mergeStdSuperMaps<BoolStdSuperMap>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            ZvalStdSuperMap *otherVec = (ZvalStdSuperMap*) otherObj->vo;

            ZvalStdSuperMap *merged = (ZvalStdSuperMap*) mergeStdSuperMaps<ZvalStdSuperMap>(vec, otherVec);
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
T* intersectStdSuperMaps(const T* vec, const T* otherVec) {
    T *intersect = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0 || otherVecSize == 0) {
        return intersect;
    }

    unordered_map<X, int> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        intersect->resize(vecSize);
    } else {
        intersect->resize(otherVecSize);
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
T* intersectZvalStdSuperMaps(const T* vec, const T* otherVec, int type) {
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
        intersect->resize(vecSize);
    } else {
        intersect->resize(otherVecSize);
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

PHP_METHOD(StdSuperMap, intersect) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, super_map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    super_map_object *otherObj = (super_map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not intersect elements in to another type of super_map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, super_map_entry);
    super_map_object* resultObject = (super_map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            IntStdSuperMap *otherVec = (IntStdSuperMap*) otherObj->vo;

            resultObject->vo = intersectStdSuperMaps<IntStdSuperMap, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            FloatStdSuperMap *otherVec = (FloatStdSuperMap*) otherObj->vo;

            resultObject->vo = intersectStdSuperMaps<FloatStdSuperMap, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringStdSuperMap *otherVec = (StringStdSuperMap*) otherObj->vo;

            resultObject->vo = intersectStdSuperMaps<StringStdSuperMap, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            BoolStdSuperMap *otherVec = (BoolStdSuperMap*) otherObj->vo;

            resultObject->vo = intersectStdSuperMaps<BoolStdSuperMap, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            ZvalStdSuperMap *otherVec = (ZvalStdSuperMap*) otherObj->vo;

            ZvalStdSuperMap *intersect = (ZvalStdSuperMap*) intersectZvalStdSuperMaps<ZvalStdSuperMap>(vec, otherVec, thisObj->type);
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
T* diffStdSuperMaps(const T* vec, const T* otherVec) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->resize(vecSize);
        diff->insert(vec->begin(), vec->end());
        return diff;
    }

    unordered_map<X, int> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        diff->resize(vecSize);
    } else {
        diff->resize(otherVecSize);
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
T* diffZvalStdSuperMaps(const T* vec, const T* otherVec, int type) {
    T *diff = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0) {
        return diff;
    } else if (otherVecSize == 0) {
        diff->resize(vecSize);
        diff->insert(vec->begin(), vec->end());
        return diff;
    }

    CompareZvalValue::type = type;
    unordered_map<zval*, int, std::hash<zval*>, CompareZvalValue> mp;

    mp.reserve(vecSize);

    if (vecSize < otherVecSize) {
        diff->resize(vecSize);
    } else {
        diff->resize(otherVecSize);
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

PHP_METHOD(StdSuperMap, diff) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, super_map_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);
    super_map_object *otherObj = (super_map_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not diff elements in to another type of super_map.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, super_map_entry);
    super_map_object* resultObject = (super_map_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
            IntStdSuperMap *otherVec = (IntStdSuperMap*) otherObj->vo;

            resultObject->vo = diffStdSuperMaps<IntStdSuperMap, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
            FloatStdSuperMap *otherVec = (FloatStdSuperMap*) otherObj->vo;

            resultObject->vo = diffStdSuperMaps<FloatStdSuperMap, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
            StringStdSuperMap *otherVec = (StringStdSuperMap*) otherObj->vo;

            resultObject->vo = diffStdSuperMaps<StringStdSuperMap, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
            BoolStdSuperMap *otherVec = (BoolStdSuperMap*) otherObj->vo;

            resultObject->vo = diffStdSuperMaps<BoolStdSuperMap, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
            ZvalStdSuperMap *otherVec = (ZvalStdSuperMap*) otherObj->vo;

            ZvalStdSuperMap *diff = (ZvalStdSuperMap*) diffZvalStdSuperMaps<ZvalStdSuperMap>(vec, otherVec, thisObj->type);
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
static int super_mapToArray(super_map_object *thisObj, zval *arr TSRMLS_DC) {
    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_long(arr, it->first, it->second);
            }
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_double(arr, it->first, it->second);
            }
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_stringl(arr, it->first, (char *) it->second.c_str(), it->second.length(), 1);
            }
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_bool(arr, it->first, it->second);
            }
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;

            array_init_size(arr, vec->size());
            for (auto it = vec->begin(); it != vec->end(); ++it) {
                add_assoc_zval(arr, it->first, it->second);
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
PHP_METHOD(StdSuperMap, serialize) {
    zval *val, *wrapper;
	php_serialize_data_t var_hash;
	smart_str buf = {0};
    zval *object = getThis();

    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

    MAKE_STD_ZVAL(wrapper);
    MAKE_STD_ZVAL(val);

    array_init(wrapper);
    add_assoc_long(wrapper, "type", thisObj->type);

    super_mapToArray(thisObj, val TSRMLS_CC);

    add_assoc_zval(wrapper, "data", val);

	Z_TYPE_P(return_value) = IS_STRING;
	Z_STRVAL_P(return_value) = NULL;
	Z_STRLEN_P(return_value) = 0;

	PHP_VAR_SERIALIZE_INIT(var_hash);
	php_var_serialize(&buf, &wrapper, &var_hash TSRMLS_CC);
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
PHP_METHOD(StdSuperMap, unserialize) {

    char *serialized = NULL;
    int buf_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &serialized, &buf_len) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

	const unsigned char *p;
	php_unserialize_data_t var_hash;

	if (buf_len == 0) {
		RETURN_FALSE;
	}

	zval *object = getThis();
    super_map_object *thisObj = (super_map_object *) zend_object_store_get_object(object TSRMLS_CC);

	zval *arr;
	MAKE_STD_ZVAL(arr);

	p = (const unsigned char*) serialized;
	PHP_VAR_UNSERIALIZE_INIT(var_hash);

	if (!php_var_unserialize(&arr, &p, p + buf_len, &var_hash TSRMLS_CC)) {
		PHP_VAR_UNSERIALIZE_DESTROY(var_hash);
		zval_dtor(arr);

		if (!EG(exception)) {
		    char buffer[512];
		    sprintf(buffer, "Error at offset %ld of %d bytes", (long)((char*)p - serialized), buf_len);
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

	thisObj->type = Z_LVAL_P(*zv_type);

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

        // by now we have data set and can use Z_ macros for accessing type and variable data.

        char *key = NULL;
        uint  klen;
        ulong index = 0;

        zend_hash_get_current_key_ex(Z_ARRVAL_P(*zv_data), &key, &klen, &index, 0, &position);

        // HASH_KEY_IS_STRING : the key is a string, key and klen will be set
        // ELSE : we assume the key to be long, index will be set

        switch (Z_LVAL_P(*zv_type)) {
            case TYPE_SCALAR_INT:
            {
                if (c == 0) {
                    IntStdSuperMap* vec = new IntStdSuperMap();
                    vec->resize(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                    thisObj->vo = vec;
                }

                IntStdSuperMap *vec = (IntStdSuperMap*) thisObj->vo;
                (*vec)[key] = Z_LVAL_P(*data);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                if (c == 0) {
                    FloatStdSuperMap* vec = new FloatStdSuperMap();
                    vec->resize(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                    thisObj->vo = vec;
                }

                FloatStdSuperMap *vec = (FloatStdSuperMap*) thisObj->vo;
                (*vec)[key] = Z_DVAL_P(*data);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                if (c == 0) {
                    StringStdSuperMap* vec = new StringStdSuperMap();
                    vec->resize(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                    thisObj->vo = vec;
                }

                StringStdSuperMap *vec = (StringStdSuperMap*) thisObj->vo;
                (*vec)[key] = Z_STRVAL_P(*data);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                if (c == 0) {
                    BoolStdSuperMap* vec = new BoolStdSuperMap();
                    vec->resize(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                    thisObj->vo = vec;
                }

                BoolStdSuperMap *vec = (BoolStdSuperMap*) thisObj->vo;
                (*vec)[key] = Z_BVAL_P(*data);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                if (c == 0) {
                    ZvalStdSuperMap* vec = new ZvalStdSuperMap();
                    vec->resize(zend_hash_num_elements(Z_ARRVAL_P(*zv_data)));
                    thisObj->vo = vec;
                }

                ZvalStdSuperMap *vec = (ZvalStdSuperMap*) thisObj->vo;
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





#endif