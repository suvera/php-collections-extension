# PHP collections extension
a C++ extension for PHP - Collections Framework

## Prerequisites
  1. <sub>PHP 5.2 or higher</sub>
  2. <sub>c++0x or higher (g++ 4.4.6 or higher), whichever supports unordered_map</sub>
  3. <sub>Make sure you've *phpize* and *php-config* installed.</sub>

## Installation
  1. <sub>cd php-collections-extension</sub>
  2. <sub>/path/to/phpize</sub>
  3. <sub>./configure --with-php-config=/path/to/php-config --enable-collections</sub>
  4. <sub>make</sub>
  5. <sub>make test # optional</sub>
  6. <sub>sudo make install</sub>

> Add *extension=collections.so* to your php.ini

> Test the code by running  **/path/to/php -d"extension=collections.so" tests/performance.php**

__Windows build is not supported yet.__

## PHP Constants

This extension comes with following predefined constants.

These constants represent Collection *Value* Type.

- 1. TYPE_SCALAR_INT

<sub>
To deal with list of Integer type values
</sub>

- 2. TYPE_SCALAR_FLOAT

<sub>
To deal with list of Float type values
</sub>

- 3. TYPE_SCALAR_STRING

<sub>
To deal with list of String type values
</sub>

- 4. TYPE_SCALAR_BOOL

<sub>
To deal with list of Boolean type values
</sub>

- 5. TYPE_COMPLEX_RESOURCE

<sub>
To deal with list of Resource type values
</sub>

- 6. TYPE_COMPLEX_OBJECT

<sub>
To deal with list of Object type values
</sub>

- 7. TYPE_COMPLEX_ARRAY

<sub>
To deal with list of Array type values
</sub>

## PHP Classes

This extension provides following collection classes

1. [StdVector](https://github.com/suvera/php-collections-extension/blob/master/docs/StdVector.md) - Vector like functionality
1. [StdMap](https://github.com/suvera/php-collections-extension/blob/master/docs/StdMap.md) - unordered_map like functionality


