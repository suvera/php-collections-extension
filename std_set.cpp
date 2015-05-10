/**
 *  StdSet class implementation
 */
PHP_METHOD(StdSet, __construct) {
    long type = 0, capacity = 0;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|l", &type, &capacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;

    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);

    thisObj->type = type;

    try {
        switch (type) {
            case TYPE_SCALAR_INT:
            {
                thisObj->vo = new IntStdSet();
                ((IntStdSet*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                thisObj->vo = new FloatStdSet();
                ((FloatStdSet*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                thisObj->vo = new StringStdSet();
                ((StringStdSet*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                thisObj->vo = new BoolStdSet();
                ((BoolStdSet*) thisObj->vo)->reserve(capacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                thisObj->vo = new ZvalStdSet();
                ((ZvalStdSet*) thisObj->vo)->reserve(capacity);
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
        zend_throw_exception(NULL, "Unknown error in StdSet::__construct", 0 TSRMLS_CC);
        return;
    }
}


PHP_METHOD(StdSet, size)
{
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    long count = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            count = ((IntStdSet*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            count = ((FloatStdSet*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            count = ((StringStdSet*) thisObj->vo)->size();
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            count = ((BoolStdSet*) thisObj->vo)->size();
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            count = ((ZvalStdSet*) thisObj->vo)->size();
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





PHP_METHOD(StdSet, reserve) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    long newCapacity = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &newCapacity) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdSet*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdSet*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdSet*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdSet*) thisObj->vo)->reserve(newCapacity);
            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ((ZvalStdSet*) thisObj->vo)->reserve(newCapacity);
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
        zend_throw_exception(NULL, "Unknown error in StdSet::reserve", 0 TSRMLS_CC);
        return;
    }
}





PHP_METHOD(StdSet, push) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            vec->insert(val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            vec->insert(val);
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

            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            vec->insert(val);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            vec->insert(val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;

            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }

            vec->insert(val);

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

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }

            if (thisObj->objCe == NULL && val != NULL) {
                thisObj->objCe = Z_OBJCE_P(val);
            }

            vec->insert(val);
            add_reference_count(val);
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }
            vec->insert(val);

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
 * Only Applicable to unordered_set<string, Object>
 */
PHP_METHOD(StdSet, getClass) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);

    if (thisObj->objCe == NULL) {
        RETURN_NULL();
    } else {
        RETURN_STRING((char *) thisObj->objCe->name, 1);
    }
}





PHP_METHOD(StdSet, erase) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    long erased = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            erased = vec->erase(val);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            double val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            erased = vec->erase(val);
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

            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            erased = vec->erase(val);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            zend_bool val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            erased = vec->erase(val);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }
            erased = vec->erase(val);
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

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }

            erased = vec->erase(val);
        }
        break;


        case TYPE_COMPLEX_ARRAY:
        {
            zval *val;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            if (vec->count(val)) {
                delete_reference_count(*(vec->find(val)));
            }
            erased = vec->erase(val);
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





PHP_METHOD(StdSet, clear) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);

    try {
        switch (thisObj->type) {
            case TYPE_SCALAR_INT:
            {
                ((IntStdSet*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_FLOAT:
            {
                ((FloatStdSet*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_STRING:
            {
                ((StringStdSet*) thisObj->vo)->clear();

            }
            break;

            case TYPE_SCALAR_BOOL:
            {
                ((BoolStdSet*) thisObj->vo)->clear();

            }
            break;

            case TYPE_COMPLEX_RESOURCE:
            case TYPE_COMPLEX_OBJECT:
            case TYPE_COMPLEX_ARRAY:
            {
                ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;

                for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                    delete_reference_count(*it);
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
        zend_throw_exception(NULL, "Unknown error in StdSet::clear", 0 TSRMLS_CC);
        return;
    }

    RETURN_TRUE;
}





// search for a Value
PHP_METHOD(StdSet, hasValue) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    zend_bool found = 0;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            long val = 0;
            if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &val) == FAILURE) {
                zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
                return;
            }

            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
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

            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            auto it = vec->find(val);
            if (it != vec->end()) {
                found = 1;
            }
        }
        break;

        default:
        {
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }

    RETURN_BOOL(found);
}








/**
 * return values as StdVector
 */
PHP_METHOD(StdSet, values) {
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    set_object *newObject;

    object_init_ex(return_value, vector_entry);
    newObject = (set_object *) zend_object_store_get_object(return_value TSRMLS_CC);

    newObject->type = thisObj->type;
    newObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            IntVector *v = new IntVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(*it);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            FloatVector *v = new FloatVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(*it);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            StringVector *v = new StringVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(*it);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            BoolVector *v = new BoolVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(*it);
            }

            newObject->vo = v;
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            ZvalVector *v = new ZvalVector();

            v->reserve(vec->size());
            for (auto it = vec->cbegin(); it != vec->cend(); ++it ) {
                v->push_back(*it);
                add_reference_count(*it);
            }

            newObject->vo = v;
        }
        break;

        default:
        {
            set_object_free_storage(newObject TSRMLS_CC);
            zend_throw_exception(NULL, "Invalid data type", 0 TSRMLS_CC);
        }
        break;
    }
}





// Apply function to all elements in this set
PHP_METHOD(StdSet, applyEach) {
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &fci, &fci_cache) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }
    zval *object = getThis();
    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            std::for_each(vec->begin(), vec->end(), ApplyEachCaller(&fci, &fci_cache));
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
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
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
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









// Take other StdSet as input append to elements into this
PHP_METHOD(StdSet, append) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, set_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    set_object *otherObj = (set_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not append elements to another type of set.", 0 TSRMLS_CC);
        return;
    }

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            IntStdSet *otherVec = (IntStdSet*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            FloatStdSet *otherVec = (FloatStdSet*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            StringStdSet *otherVec = (StringStdSet*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            BoolStdSet *otherVec = (BoolStdSet*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());
            vec->insert(otherVec->begin(), vec->end());
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            ZvalStdSet *otherVec = (ZvalStdSet*) otherObj->vo;
            vec->reserve(vec->size() + otherVec->size());

            for (auto it = otherVec->begin(); it != otherVec->end(); ++it) {
                if (!vec->count(*it)) {
                    vec->insert(*it);
                    add_reference_count(*it);
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

// Take other StdSet as input and return StdSet
template<class T>
T* mergeStdSets(const T* vec, const T* otherVec) {
    T *merged = new T();

    merged->reserve(vec->size() + otherVec->size());

    merged->insert(vec->begin(), vec->end());
    merged->insert(otherVec->begin(), otherVec->end());

    return merged;
}


PHP_METHOD(StdSet, merge) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, set_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    set_object *otherObj = (set_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not merge elements in to another type of set.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, set_entry);
    set_object* resultObject = (set_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            IntStdSet *otherVec = (IntStdSet*) otherObj->vo;

            resultObject->vo = mergeStdSets<IntStdSet>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            FloatStdSet *otherVec = (FloatStdSet*) otherObj->vo;

            resultObject->vo = mergeStdSets<FloatStdSet>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            StringStdSet *otherVec = (StringStdSet*) otherObj->vo;

            resultObject->vo = mergeStdSets<StringStdSet>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            BoolStdSet *otherVec = (BoolStdSet*) otherObj->vo;

            resultObject->vo = mergeStdSets<BoolStdSet>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            ZvalStdSet *otherVec = (ZvalStdSet*) otherObj->vo;

            ZvalStdSet *merged = (ZvalStdSet*) mergeStdSets<ZvalStdSet>(vec, otherVec);
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
T* intersectStdSets(const T* vec, const T* otherVec) {
    T *intersect = new T();

    uLongInt vecSize = vec->size();
    uLongInt otherVecSize = otherVec->size();

    if (vecSize == 0 || otherVecSize == 0) {
        return intersect;
    }

    if (vecSize < otherVecSize) {
        intersect->reserve(vecSize);
    } else {
        intersect->reserve(otherVecSize);
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (otherVec->count(*it)) {
            intersect->insert(*it);
        }
    }

    return intersect;
}

PHP_METHOD(StdSet, intersect) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, set_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    set_object *otherObj = (set_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not intersect elements in to another type of set.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, set_entry);
    set_object* resultObject = (set_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            IntStdSet *otherVec = (IntStdSet*) otherObj->vo;

            resultObject->vo = intersectStdSets<IntStdSet, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            FloatStdSet *otherVec = (FloatStdSet*) otherObj->vo;

            resultObject->vo = intersectStdSets<FloatStdSet, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            StringStdSet *otherVec = (StringStdSet*) otherObj->vo;

            resultObject->vo = intersectStdSets<StringStdSet, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            BoolStdSet *otherVec = (BoolStdSet*) otherObj->vo;

            resultObject->vo = intersectStdSets<BoolStdSet, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            ZvalStdSet *otherVec = (ZvalStdSet*) otherObj->vo;

            ZvalStdSet *intersect = (ZvalStdSet*) intersectStdSets<ZvalStdSet, zval>(vec, otherVec);
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
T* diffStdSets(const T* vec, const T* otherVec) {
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

    if (vecSize < otherVecSize) {
        diff->reserve(vecSize);
    } else {
        diff->reserve(otherVecSize);
    }

    for (auto it = vec->begin(); it != vec->end(); ++it) {
        if (otherVec->count(*it)) {
            diff->insert(*it);
        }
    }

    return diff;
}

PHP_METHOD(StdSet, diff) {
    zval *other;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &other, set_entry) == FAILURE) {
        zend_throw_exception(NULL, "Invalid input parameters to the method, please check the method signature.", 0 TSRMLS_CC);
        return;
    }

    zval *object = getThis();

    set_object *thisObj = (set_object *) zend_object_store_get_object(object TSRMLS_CC);
    set_object *otherObj = (set_object *) zend_object_store_get_object(other TSRMLS_CC);

    if (thisObj->type != otherObj->type) {
        zend_throw_exception(NULL, "Could not diff elements in to another type of set.", 0 TSRMLS_CC);
        return;
    }

    object_init_ex(return_value, set_entry);
    set_object* resultObject = (set_object *) zend_object_store_get_object(return_value TSRMLS_CC);
    resultObject->type = thisObj->type;
    resultObject->objCe = thisObj->objCe;

    switch (thisObj->type) {
        case TYPE_SCALAR_INT:
        {
            IntStdSet *vec = (IntStdSet*) thisObj->vo;
            IntStdSet *otherVec = (IntStdSet*) otherObj->vo;

            resultObject->vo = diffStdSets<IntStdSet, long>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_FLOAT:
        {
            FloatStdSet *vec = (FloatStdSet*) thisObj->vo;
            FloatStdSet *otherVec = (FloatStdSet*) otherObj->vo;

            resultObject->vo = diffStdSets<FloatStdSet, double>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_STRING:
        {
            StringStdSet *vec = (StringStdSet*) thisObj->vo;
            StringStdSet *otherVec = (StringStdSet*) otherObj->vo;

            resultObject->vo = diffStdSets<StringStdSet, string>(vec, otherVec);
        }
        break;

        case TYPE_SCALAR_BOOL:
        {
            BoolStdSet *vec = (BoolStdSet*) thisObj->vo;
            BoolStdSet *otherVec = (BoolStdSet*) otherObj->vo;

            resultObject->vo = diffStdSets<BoolStdSet, bool>(vec, otherVec);
        }
        break;

        case TYPE_COMPLEX_RESOURCE:
        case TYPE_COMPLEX_OBJECT:
        case TYPE_COMPLEX_ARRAY:
        {
            ZvalStdSet *vec = (ZvalStdSet*) thisObj->vo;
            ZvalStdSet *otherVec = (ZvalStdSet*) otherObj->vo;

            ZvalStdSet *diff = (ZvalStdSet*) diffStdSets<ZvalStdSet, zval>(vec, otherVec);
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