--TEST--
Check for StdSet presence
--SKIPIF--
<?php if (!extension_loaded("collections")) print "skip"; ?>
--FILE--
<?php

$obj = new StdSet(TYPE_SCALAR_INT);

if (TYPE_SCALAR_FLOAT !== 2) {
    echo "Failed TYPE_SCALAR_FLOAT must be 2 \n";
}

try {
    $obj = new StdSet(100);
    echo "Failed\n";
} catch (Exception $ex) {
    //echo $ex->getMessage() . "\n";
}


$obj = new StdSet(TYPE_SCALAR_INT);
if ($obj->size() !== 0) {
    echo "Failed \$obj->size() must be 0 \n";
}

$arr = array(10, 5, 8, 3, 1, 9);
foreach ($arr as $indx => $num) {
    $obj->push($num);
    if ($obj->size() !== ($indx+1)) {
        echo "Failed \$obj->size() must be " . ($indx+1) . ', But received ' . $obj->size() ." \n";
    }
}

foreach ($arr as $indx => $num) {
    if (!$obj->hasValue($num)) {
        echo "Failed value in \$obj->hasValue('$num') must be " . $num ." \n";
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
