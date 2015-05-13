# StdSet

StdSet is a container that store *unique* elements in no particular order,
and which allow for fast retrieval of individual elements based on their value.

>> Note: PHP does not have Set like functionality in-built.

Simple Example:

```php
// Set of integer values
$obj = new StdSet(TYPE_SCALAR_INT);
$obj->push(500);
$obj->push(67);
$obj->push(0);

echo 'My Set size is ' . $obj->size() . " \n";

$obj->applyEach(function($val) {
    echo "Item: $val \n";
});
```

##### Notes
> StdSet does not store NULL values  (but you can store NULL for vector of type **TYPE_COMPLEX_OBJECT** )

```php
// Set of String values
$obj = new StdSet(TYPE_SCALAR_STRING);
$obj->push('github');
$obj->push('google');
$obj->push('bing');

echo 'My Set size is ' . $obj->size() . " \n";

$obj->applyEach(function($val) {
    echo "Item: $val \n";
});
```

#### Class Signature

```php
class StdSet {
    /**
     * @param int $type
     */
    public function __construct($type) {}

    /**
     * @return int
     */
    public function size() {}

    /**
     * @param int $capacity
     */
    public function reserve($capacity) {}

    /**
     * @param mixed $item
     */
    public function push($item) {}

    /**
     * @param string $item
     */
    public function erase($item) {}

    public function clear() {}

    /**
     * @return string|null
     */
    public function getClass() {}

    /**
     * @param mixed $item
     * @return bool
     */
    public function hasValue($item) {}

    /**
     * @param callback
     */
    public function applyEach(callback) {}

}
```

#### Performance

<sub>Tested with 2GB memory Limit on 64 bit machine.</sub>

<sub>Tested with PHP 5.4.24</sub>

<sub>Tested with 1 million items.</sub>

>> when you want to use PHP array as a Set then you have to make sure that
>> all elements are unique, that is nature of a Set.
>> to do so, you have to use in_array() or array_search() before insert
>> but that will take forever.
>> Since PHP does not have Set like functionality in-built, these statistics may be wrong.


| Test   | PHP Array (secs) | StdSet (secs) |
| :----- | ---------------: | ---------------: |
| Creation - Integer values | 0.46283317 | 0.35474396 |
| Creation - Object values | 1.7613399 | 1.6478591 |
| in_array - Integer values | 0.01591301 | 0.00000501 |
| in_array - Object values | 0.05098796 | 0.00001311 |
| in_array - for unknown value | 0.05051899 | 0.00001192 |
| array_values - Integer values | 0.24997211 | 0.00725293 (StdVector) |



**Memory**

<sub>Tested with 1 million integer items.</sub>

| Test   | PHP Array (MB) | StdSet (MB) |
| :----- | ---------------: | ---------------: |
| memory_get_peak_usage | 137.92 | 38.8 |
| zsh (time command) max memory | 154 | 53  |
