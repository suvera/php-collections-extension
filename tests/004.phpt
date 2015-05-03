--TEST--
Check for StdMap presence
--SKIPIF--
<?php if (!extension_loaded("collections")) print "skip"; ?>
--FILE--
<?php

$obj = new StdMap(TYPE_SCALAR_INT);

if (TYPE_SCALAR_FLOAT !== 2) {
    echo "Failed TYPE_SCALAR_FLOAT must be 2 \n";
}

try {
    $obj = new StdMap(100);
    echo "Failed\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}


$obj = new StdMap(TYPE_SCALAR_INT);
if ($obj->size() !== 0) {
    echo "Failed \$obj->size() must be 0 \n";
}

$arr = array(10, 5, 8, 3, 1, 9);
foreach ($arr as $indx => $num) {
    $obj->push($indx, $num);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed \$obj->size() must be " . ($indx+1) . ', But received ' . $obj->size() ." \n";
    }
}

foreach ($arr as $indx => $num) {
    if ($obj->at($indx) !== $num) {
        echo "Failed value in \$obj->at('$indx') must be " . $num ." \n";
    }
}

$len = $obj->size();
for ($i = 0; $i < $len; $i++) {
    //echo $obj->at($i) . " ";
}
//echo "\n";

$obj->erase('3');
if ($obj->size() !== $len-1) {
    echo "Failed \$obj->size() must be 2 \n";
}



echo "collections extension is available";
?>
--EXPECT--
collections extension is available
