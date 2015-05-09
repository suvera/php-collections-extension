# StdMap

StdMap is a associative container that store elements formed by the combination of a key value and a mapped value.

Key - must be a string, cannot be NULL

Value - can be anything (can be NULL for object type)


Simple Example:

```php
// Map of integer values
$obj = new StdMap(TYPE_SCALAR_INT);
$obj->push('k1', 500);
$obj->push('k2', 67);
$obj->push('k3', 0);

echo 'My Map size is ' . $obj->size() . " \n";

echo 'Item-1: ' . $map->at('k1') . "\n";
echo 'Item-2: ' . $map->at('k2') . "\n";
echo 'Item-3: ' . $map->at('k3') . "\n";
```

##### Notes
> StdMap does not store NULL values  (but you can store NULL for vector of type **TYPE_COMPLEX_OBJECT** )

```php
// Map of String values
$obj = new StdMap(TYPE_SCALAR_STRING);
$obj->push('git', 'github');
$obj->push('goog', 'google');
$obj->push('b', 'bing');

$obj->applyEach(function($value, $key) {
    echo "$key = $val \n";
});
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
     * @param string $key
     * @return mixed
     */
    public function at($key) {}

    /**
     * @param string $key
     * @param mixed $item
     */
    public function push($key, $item) {}

    /**
     * @param string $key
     * @param mixed $item
     */
    public function replace($key, $item) {}

    /**
     * @param string $key
     */
    public function erase($key) {}

    public function clear() {}

    /**
     * @param mixed $item
     * @return int
     */
    public function search($item) {}

    /**
     * @return string|null
     */
    public function getClass() {}

    /**
     * @param mixed $value
     * @return bool
     */
    public function hasValue($value) {}

    /**
     * @param string $key
     * @return bool
     */
    public function hasKey($key) {}

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


| Test   | PHP Array (secs) | StdMap (secs) |
| :----- | ---------------: | ---------------: |
| Creation - Integer values | 0.48740792 | 0.95970893 |
| Search a Item - Integer values | 0.01030397 | 0.01316404  |
| Access all Elements in a loop - Integer values | 0.42662787437439 | 0.69262599945068 |
| Get array_keys() | 0.39861703 | 0.08291602 (returns StdVector) |
| Creation - Object values | 1.32240295 | 2.20958304 |
| Search Known Item - Object values | 0.05964589 | 0.00614095  |
| Search Unknown Item - Object values | 0.06554985 | 0.1092279  |

**Memory**

<sub>Tested with 1 million integer items.</sub>

| Test   | PHP Array (MB) | StdMap (MB) |
| :----- | ---------------: | ---------------: |
| memory_get_peak_usage | 153.1 | 0.22 |
| zsh (time command) max memory | 163 | 107  |
