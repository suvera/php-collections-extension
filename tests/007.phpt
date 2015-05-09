--TEST--
Check for StdSet functionality
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

$obj = new StdSet(TYPE_COMPLEX_OBJECT);

if ($obj->size() !== 0) {
    echo "Failed \$obj->size() must be 0 \n";
}

try {
    @$obj->push(100);
    echo "Failed\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}

$memSize = 216;
$arr = array(10, 5, 8, 3, 1, 9);
$memcgeck = array(2, 1, 1, 1, 1, 1, 1, 8, 9, 10);

$memcgeck[0] = memory_get_usage();
$obj0 = new StdSet(TYPE_COMPLEX_OBJECT);
$memcgeck[1] = memory_get_usage();
$obj1 = new StdSet(TYPE_COMPLEX_OBJECT);
$memcgeck[2] = memory_get_usage();
$obj2 = new StdSet(TYPE_COMPLEX_OBJECT);
$memcgeck[3] = memory_get_usage();
$obj3 = new StdSet(TYPE_COMPLEX_OBJECT);
$memcgeck[4] = memory_get_usage();
$obj4 = new StdSet(TYPE_COMPLEX_OBJECT);
$memcgeck[5] = memory_get_usage();

unset($obj0, $obj1, $obj2, $obj3, $obj4);
$memcgeck[6] = memory_get_usage();

if ($memcgeck[1]-$memcgeck[0] !== $memSize) {
    echo "Failed Object creation leaks memory $memcgeck[0]  !== $memcgeck[1] \n";
}

if ($memcgeck[6] !== $memcgeck[0]) {
    echo "Failed Object unset() leaks memory $memcgeck[0]  !== $memcgeck[6] \n";
}



$memcgeck[7] = memory_get_usage();
$obj5 = new StdSet(TYPE_COMPLEX_OBJECT);
$obj5->push(new ABC(190));
$obj5->push(new ABC(10));
$obj5->push(new ABC(1));
$obj5->push(new ABC(0));
$memcgeck[8] = memory_get_usage();
unset($obj5);
$memcgeck[9] = memory_get_usage();

//print_r($memcgeck);

foreach ($arr as $indx => $num) {
    $obj->push(new ABC($num));
    if ($obj->size() !== ($indx+1)) {
        echo "Failed1 \$obj->size() must be " . ($indx+1) ." \n";
    }
}

$arr = array(new ABC(10), new ABC(5), new ABC(8), new ABC(3), new ABC(1), new ABC(9));

$obj = new StdSet(TYPE_COMPLEX_OBJECT);
if ($obj->size() !== 0) {
    echo "Failed2 \$obj->size() must be 0 \n";
}

foreach ($arr as $indx => $objA) {
    $obj->push($objA);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed3 \$obj->size() must be " . ($indx+1) ." \n";
    }
}

unset($obj);

if ($arr[1]->num !== 5) {
    echo "Failed4 value arr[1]->num  must be 5 \n";
}


$i = 0;
$mem = 0;
while ($i < 5) {
    $obj = new StdSet(TYPE_COMPLEX_OBJECT);
    foreach ($arr as $indx => $objA) {
        $obj->push($objA);
        if ($obj->size() !== ($indx+1)) {
            echo "Failed5 \$obj->size() must be " . ($indx+1) ." \n";
        }
    }

    if ($mem === 0) {
        $mem = memory_get_usage();
    } else if (memory_get_usage() !== $mem) {
        echo "Failed6 memroy leaked\n";
    }
    $i++;
}

if ($arr[1]->num !== 5) {
    echo "Failed7 value arr[1]->num  must be 5 \n";
}

$obj = new StdSet(TYPE_COMPLEX_OBJECT);
foreach ($arr as $indx => $objA) {
    $obj->push($objA);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed8 \$obj->size() must be " . ($indx+1) ." \n";
    }
}

$i = 0;
//while ($obj->hasNext()) {
//    $a = $obj->getValue();
//}

foreach ($arr as $indx => $number) {
    if (!$obj->hasValue($number)) {
        echo "Failed value in \$number must be " . $number->num ." \n";
    }
}



try {
    @$obj->push(new XYZ());
    echo "Failed, StdSet should not accept other objects.\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}

$obj->push(new OPQ(45));



$map = new StdSet(TYPE_COMPLEX_OBJECT);
$map->push(new ABC(190));
$map->push(new ABC(10));
$map->push(new ABC(1));
$map->push(new ABC(0));

$vec = $map->values();
if ($vec->size() != 4) {
    echo '1. $vec size should be 4 ' . "\n";
}


$map = new StdSet(TYPE_COMPLEX_OBJECT);
$map->push(new ABC(190));
$map->push(new ABC(10));
$map->push(new ABC(1));
$map->push(new ABC(0));

$vec = $map->values();
if ($map->size() != $vec->size()) {
    echo "Filed StdSet::values(), map Size: " . $map->size() . ' ';
    echo "Vec Size: " . $vec->size() . "\n";
}


echo "collections extension is available";
?>
--EXPECT--
collections extension is available
