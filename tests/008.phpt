--TEST--
Check for merge/intersect/diff functionality
--SKIPIF--
<?php if (!extension_loaded("collections")) print "skip"; ?>
--FILE--
<?php

class ABC {
    public $a = 'a+b+c';
    public $num;

    function __construct($num) {
        $this->num = $num;
    }
}

class XYZ {
    public $a = 'x+y+z';
}

class OPQ extends ABC {
    public $a = 'o+p+q';
}

$obj = new StdVector(TYPE_SCALAR_INT);
$obj->push(2);
$obj->push(4);
$obj->push(6);

$obj2 = new StdVector(TYPE_SCALAR_INT);
$obj2->push(3);
$obj2->push(5);
$obj2->push(7);

$obj->append($obj2);
if ($obj->size() != 6) {
    echo "StdVector, append does not work. size should be 6, actual " . $obj->size() . "\n";
}

$obj3 = new StdVector(TYPE_SCALAR_INT);
$obj3->push(11);
$obj3->push(13);
$obj3->push(15);

$obj4 = $obj2->merge($obj3);
if ($obj4->size() != 6) {
    echo "StdVector, merge does not work. size should be 6, actual " . $obj4->size() . "\n";
}

$obj4->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj5 = $obj->merge($obj4);
if ($obj5->size() != 12) {
    echo "StdVector, merge does not work. size should be 9, actual " . $obj5->size() . "\n";
}

$obj5 = $obj->diff($obj2);
if ($obj5->size() != 3) {
    echo "StdVector, diff does not work. size should be 3, actual " . $obj5->size() . "\n";
}

$obj5->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj5 = $obj->intersect($obj2);
if ($obj5->size() != 3) {
    echo "StdVector, intersect does not work. size should be 3, actual " . $obj5->size() . "\n";
}

$obj5->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});




$obj = new StdMap(TYPE_SCALAR_INT);
$obj->push('two', 2);
$obj->push('four', 4);
$obj->push('six', 6);

$obj2 = new StdMap(TYPE_SCALAR_INT);
$obj2->push('three', 3);
$obj2->push('five', 5);
$obj2->push('seven', 7);

$obj3 = $obj->merge($obj2);
if ($obj3->size() != 6) {
    echo "StdMap, merge does not work. size should be 6, actual " . $obj3->size() . "\n";
}

$obj3->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj4 = $obj3->intersect($obj2);
if ($obj4->size() != 3) {
    echo "StdMap, intersect does not work. size should be 3, actual " . $obj4->size() . "\n";
}

$obj4->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj4 = $obj3->diff($obj2);
if ($obj4->size() != 3) {
    echo "StdMap, diff does not work. size should be 3, actual " . $obj4->size() . "\n";
}

$obj4->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});



$obj = new StdSet(TYPE_SCALAR_INT);
$obj->push(2);
$obj->push(4);
$obj->push(6);

$obj2 = new StdSet(TYPE_SCALAR_INT);
$obj2->push(3);
$obj2->push(5);
$obj2->push(7);

$obj2->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj3 = $obj->merge($obj2);
if ($obj3->size() != 6) {
    echo "StdSet, merge does not work. size should be 6, actual " . $obj3->size() . "\n";
}

$obj3->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj4 = $obj3->intersect($obj2);
if ($obj4->size() != 3) {
    echo "StdSet, intersect does not work. size should be 3, actual " . $obj4->size() . "\n";
}

$obj4->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

$obj4 = $obj3->diff($obj2);
if ($obj4->size() != 3) {
    echo "StdSet, diff does not work. size should be 3, actual " . $obj4->size() . "\n";
}

$obj4->applyEach(function($val, $index) {
    //echo "$index = $val\n";
});

echo "collections extension is available";
?>
--EXPECT--
collections extension is available
