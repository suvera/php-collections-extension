--TEST--
Check for collections functionality
--SKIPIF--
<?php if (!extension_loaded("collections")) print "skip"; ?>
--FILE--
<?php

$obj = new StdVector(TYPE_SCALAR_INT);
if ($obj->size() !== 0) {
    echo "Failed \$obj->size() must be 0 \n";
}

$arr = array(10, 5, 8, 3, 1, 9);
foreach ($arr as $indx => $num) {
    $obj->push($num);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed \$obj->size() must be " . ($indx+1) ." \n";
    }
}

// insert


foreach ($arr as $indx => $num) {
    if ($obj->at($indx) !== $num) {
        echo "Failed value in \$obj->at('$indx') must be " . $num ." \n";
    }
}

sort($arr, SORT_NUMERIC);
$obj->sort();

foreach ($arr as $indx => $num) {
    if ($obj->at($indx) !== $num) {
        echo "Failed Sorted value in \$obj->at('$indx') must be " . $num ." \n";
    }
}

$len = $obj->size();
for ($i = 0; $i < $len; $i++) {
    //echo $obj->at($i) . " ";
}
//echo "\n";

$obj->erase(2, 6000);
if ($obj->size() !== 2) {
    echo "Failed \$obj->size() must be 2 \n";
}



echo "collections extension is available";
?>
--EXPECT--
collections extension is available
