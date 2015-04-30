# PHP collections extension
a C++ extension for PHP - Collections Framework

## Prerequisites
  1. PHP 5.2 or higher
  2. c++0x or higher (g++ 4.4.6 or higher)
  3. Make sure you've *phpize* and *php-config* installed.

## Installation
  1. _cd php-collections-extension_
  2. _/path/to/phpize_
  3. _./configure --with-php-config=/path/to/php-config --enable-collections_
  4. _make_
  5. _make test_ # optional
  6. _sudo make install_

> Add *extension=collections.so* to your php.ini

> Test the code by running  **/path/to/php -d"extension=collections.so" tests/performance.php**

__Windows build is not supported yet.__

## PHP Constants

This extension comes with following predefined constants.

These constants represent Collection *Value* Type.

##### 1. TYPE_SCALAR_INT
To deal with list of Integer type values

##### 2. TYPE_SCALAR_FLOAT
To deal with list of Float type values

##### 3. TYPE_SCALAR_STRING
To deal with list of String type values

##### 4. TYPE_SCALAR_BOOL
To deal with list of Boolean type values

##### 5. TYPE_COMPLEX_RESOURCE
To deal with list of Resource type values

##### 6. TYPE_COMPLEX_OBJECT
To deal with list of Object type values

##### 7. TYPE_COMPLEX_ARRAY
To deal with list of Array type values


## PHP Classes

This extension provides following collection classes

1. StdVector - Vector like functionality


## StdVector

Simple Example:


```php
// List of integer values
$vector = new StdVector(TYPE_SCALAR_INT);
$obj->push(500);
$obj->push(67);
$obj->push(0);

echo 'My Vector size is ' . $vector->size() . " \n";

echo 'Item-1: ' . $vector->at(0) . "\n";
echo 'Item-2: ' . $vector->at(1) . "\n";
echo 'Item-3: ' . $vector->at(2) . "\n";
```

##### Notes
> StdVector does not store NULL values  (but you can store NULL for vector of type **TYPE_COMPLEX_OBJECT** )

```php
// List of String values
$vector = new StdVector(TYPE_SCALAR_STRING);
$obj->push('github');
$obj->push('google');
$obj->push('bing');

echo 'My Vector size is ' . $vector->size() . " \n";

echo 'Item-1: ' . $vector->at(0) . "\n";
echo 'Item-2: ' . $vector->at(1) . "\n";
echo 'Item-3: ' . $vector->at(2) . "\n";
```

#### Class Signature

```php
class StdVector {
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
     * @param int $pos
     * @return mixed
     */
    public function at($pos = 0) {}

    /**
     * @param mixed $item
     */
    public function push($item) {}

    /**
     * @param int  $pos
     * @param mixed $item
     */
    public function insert($pos = 0, $item = NULL) {}

    /**
     * @param int  $pos
     * @param mixed $item
     */
    public function replace($pos = 0, $item = NULL) {}

    /**
     * @param int $pos
     */
    public function erase($pos = 0) {}

    public function clear() {}

    /**
     * @param null|callback $func
     */
    public function sort($func=null) {}

    /**
     * @param mixed $item
     * @return int
     */
    public function search($item) {}

    /**
     * @return string|null
     */
    public function getClass() {}


    public function searchLast() {}

    public function reverse() {}

    public function applyEach() {}

    public function countValue() {}

    public function fill() {}

    public function unique() {}

    public function replaceIf() {}

    public function removeIf() {}

    /**
     * @return bool
     */
    public function hasNext() {}

    public function hasPrev() {}

    public function moveFirst() {}

    public function moveLast() {}

    public function getPointer() {}

    public function getIndex() {}

    /**
     * @return mixed
     */
    public function getValue() {}

    public function seek() {}

    public function append() {}

    public function merge() {}

    public function intersect() {}

    public function diff() {}
}
```

#### Performance

Tested with 2GB memory Limit on 64 bit machine.

Tested with PHP 5.4.24

Tested with 1 million items.

| Test   | PHP Array (secs) | StdVector (secs) |
| :----- | ---------------: | ---------------: |
| Creation - Integer values | 0.47556496 | 0.24744892 |
| Search a Item - Integer values | 0.01525784 | 0.00062323  |
| Access all Elements in a loop - Integer values | 0.10645294189453 | 0.23335313796997 |
| Sorting - Integer values | 2.98080301 | 0.11331296 |
| Creation - Object values | 2.17555594 | 1.16875815 |
| Search Known Item - Object values | 0.11344886 | 0.05637288  |
| Search Unknown Item - Object values | 0.11401391 | 0.05629301  |

**Memory**
Tested with 1 million integer items.

| Test   | PHP Array (MB) | StdVector (MB) |
| :----- | ---------------: | ---------------: |
| memory_get_peak_usage | 137.92 | 0.22 |
| zsh (time commmand) max memory | 154 | 24  |
