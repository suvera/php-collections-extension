--TEST--
Check for StdMap functionality
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

$obj = new StdMap(TYPE_COMPLEX_OBJECT);

if ($obj->size() !== 0) {
    echo "Failed \$obj->size() must be 0 \n";
}

try {
    @$obj->push(100, 100);
    echo "Failed\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}

$memSize = 384;
$arr = array(10, 5, 8, 3, 1, 9);
$memcgeck = array(2, 1, 1, 1, 1, 1, 1, 8, 9, 10);

$memcgeck[0] = memory_get_usage();
$obj0 = new StdMap(TYPE_COMPLEX_OBJECT);
$memcgeck[1] = memory_get_usage();
$obj1 = new StdMap(TYPE_COMPLEX_OBJECT);
$memcgeck[2] = memory_get_usage();
$obj2 = new StdMap(TYPE_COMPLEX_OBJECT);
$memcgeck[3] = memory_get_usage();
$obj3 = new StdMap(TYPE_COMPLEX_OBJECT);
$memcgeck[4] = memory_get_usage();
$obj4 = new StdMap(TYPE_COMPLEX_OBJECT);
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
$obj5 = new StdMap(TYPE_COMPLEX_OBJECT);
$obj5->push(190, new ABC(190));
$obj5->push(10, new ABC(10));
$obj5->push(1, new ABC(1));
$obj5->push(0, new ABC(0));
$memcgeck[8] = memory_get_usage();
unset($obj5);
$memcgeck[9] = memory_get_usage();

//print_r($memcgeck);

foreach ($arr as $indx => $num) {
    $obj->push($indx, new ABC($num));
    if ($obj->size() !== ($indx+1)) {
        echo "Failed1 \$obj->size() must be " . ($indx+1) ." \n";
    }
}

$arr = array(new ABC(10), new ABC(5), new ABC(8), new ABC(3), new ABC(1), new ABC(9));

$obj = new StdMap(TYPE_COMPLEX_OBJECT);
if ($obj->size() !== 0) {
    echo "Failed2 \$obj->size() must be 0 \n";
}

foreach ($arr as $indx => $objA) {
    $obj->push($indx, $objA);
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
    $obj = new StdMap(TYPE_COMPLEX_OBJECT);
    foreach ($arr as $indx => $objA) {
        $obj->push($indx, $objA);
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

$obj = new StdMap(TYPE_COMPLEX_OBJECT);
foreach ($arr as $indx => $objA) {
    $obj->push($indx, $objA);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed8 \$obj->size() must be " . ($indx+1) ." \n";
    }
}

foreach ($arr as $indx => $number) {
    $a = $obj->at($indx);
    if ($a->num !== $number->num) {
        echo "Failed value in obj->at('$indx') must be " . $a->num . ' !== ' . $number->num ." \n";
    }
}



try {
    @$obj->push(100, new XYZ());
    echo "Failed, StdMap should not accept other objects.\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}

$obj->push(45, new OPQ(45));



$map = new StdMap(TYPE_COMPLEX_OBJECT);
$map->push(190, new ABC(190));
$map->push(10, new ABC(10));
$map->push(1, new ABC(1));
$map->push(0, new ABC(0));

$vec = $map->keys();
if ($vec->size() != 4) {
    echo '1. $vec size should be 4 ' . "\n";
}

$vec->replace(0, 888);
if ($vec->at(0) != 888) {
    echo '2. $vec->at(0) should match 888 ' . "\n";
}
if ($map->at('190')->num != 190) {
    echo '2. $map->at(0)->num should match 190 ' . "\n";
}

$map->at('190')->num = 300;
if ($vec->at(0) != 888) {
    echo '3. $vec->at(0) should match 888 ' . "\n";
}
if ($map->at('190')->num != 300) {
    echo '3. $map->at(0)->num should match 300 ' . "\n";
}


$map = new StdMap(TYPE_COMPLEX_OBJECT);
$map->push(190, new ABC(190));
$map->push(10, new ABC(10));
$map->push(1, new ABC(1));
$map->push(0, new ABC(0));

$vec = $map->values();
if ($map->size() != $vec->size()) {
    echo "Filed StdMap::values(), map Size: " . $map->size() . ' ';
    echo "Vec Size: " . $vec->size() . "\n";
}

$vec->replace(0, new ABC(888));
if ($vec->at(0)->num != 888) {
    echo '2.StdMap::values() $vec->at(0) should match 888 ' . "\n";
}
if ($map->at('190')->num != 190) {
    echo '2.StdMap::values() $map->at(0)->num should match 190 ' . "\n";
}

$map->at('190')->num = 300;
if ($vec->at(0)->num != 888) {
    echo '3.StdMap::values() $vec->at(0) should match 888 ' . "\n";
}
if ($map->at('190')->num != 300) {
    echo '3.StdMap::values() $map->at(0)->num should match 300 ' . "\n";
}



echo "collections extension is available";
?>
--EXPECT--
collections extension is available
