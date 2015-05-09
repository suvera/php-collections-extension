# StdSet

StdSet is a container that store *unique* elements in no particular order,
and which allow for fast retrieval of individual elements based on their value.

Simple Example:

```php
// Set of integer values
$obj = new StdSet(TYPE_SCALAR_INT);
$obj->push(500);
$obj->push(67);
$obj->push(0);

echo 'My Set size is ' . $obj->size() . " \n";

$obj->applyEach(function($value) {
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

$obj->applyEach(function($value) {
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


| Test   | PHP Array (secs) | StdSet (secs) |
| :----- | ---------------: | ---------------: |
| Creation - Integer values | x | y |



**Memory**

<sub>Tested with 1 million integer items.</sub>

| Test   | PHP Array (MB) | StdSet (MB) |
| :----- | ---------------: | ---------------: |
| memory_get_peak_usage | X | y |
| zsh (time command) max memory | X | y  |
