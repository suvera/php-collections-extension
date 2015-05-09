# StdMap

StdMap is a container that store *unique* elements in no particular order,
and which allow for fast retrieval of individual elements based on their value.

Simple Example:

```php
// Map of integer values
$map = new StdMap(TYPE_SCALAR_INT);
$obj->push(500);
$obj->push(67);
$obj->push(0);

echo 'My Map size is ' . $map->size() . " \n";

while ($obj->hasNext()) {
    $val = $obj->getValue();
    echo "Item: $val \n";
}
```

##### Notes
> StdMap does not store NULL values  (but you can store NULL for vector of type **TYPE_COMPLEX_OBJECT** )

```php
// Map of String values
$map = new StdMap(TYPE_SCALAR_STRING);
$obj->push('github');
$obj->push('google');
$obj->push('bing');

echo 'My Map size is ' . $map->size() . " \n";

while ($obj->hasNext()) {
    $val = $obj->getValue();
    echo "Item: $val \n";
}
```

#### Class Signature

```php
class StdMap {
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

}
```

#### Performance

<sub>Tested with 2GB memory Limit on 64 bit machine.</sub>

<sub>Tested with PHP 5.4.24</sub>

<sub>Tested with 1 million items.</sub>


| Test   | PHP Array (secs) | StdMap (secs) |
| :----- | ---------------: | ---------------: |
| Creation - Integer values | x | y |



**Memory**

<sub>Tested with 1 million integer items.</sub>

| Test   | PHP Array (MB) | StdMap (MB) |
| :----- | ---------------: | ---------------: |
| memory_get_peak_usage | X | y |
| zsh (time command) max memory | X | y  |
