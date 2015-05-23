<?php
$limit = 1000000;

$time = microtime(true);
$arr = array();
for ($i =0; $i < $limit; $i++) {
    $arr[] = $i;
}
unset($arr);
echo 'Array<Int> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


$time = microtime(true);
$obj = new StdVector(TYPE_SCALAR_INT);
for ($i =0; $i < $limit; $i++) {
    $obj->push($i);
}
unset($obj);
echo 'StdVector<Int> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


// in_array  check performance on Int
$arr = array();
for ($i =0; $i < $limit; $i++) {
    $arr[] = $i;
}
$time = microtime(true);
$pos = array_search(($limit/2)-1, $arr);
echo 'search on Array<Int> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($arr);


$obj = new StdVector(TYPE_SCALAR_INT);
for ($i =0; $i < $limit; $i++) {
    $obj->push($i);
}
$time = microtime(true);
$pos = $obj->search(($limit/2)-1);
echo 'search on StdVector<Int> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($obj);


class ABC {
    public $a = 'a+b+c';
    public $num;

    function __construct($num) {
        $this->num = $num;
    }

    function __destruct() {
        //echo "__destruct on {$this->num} called\n";
    }
}


$time = microtime(true);
$arr = array();
for ($i =0; $i < $limit; $i++) {
    $arr[] = new ABC($i);
}
unset($arr);
echo 'Array<Object> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


$time = microtime(true);
$obj = new StdVector(TYPE_COMPLEX_OBJECT);
for ($i =0; $i < $limit; $i++) {
    $obj->push(new ABC($i));
}
unset($obj);
echo 'StdVector<Object> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


// sorting
$arr = array();
for ($i =0; $i < $limit; $i++) {
    $arr[] = mt_rand(0, $limit);
}
$time = microtime(true);
for ($i =0; $i < $limit; $i++) {
    $value = $arr[$i];
}
echo 'Access element in Array<int> Time: '. round(microtime(true) - $time, 40) . " secs\n";
$time = microtime(true);
sort($arr, SORT_NUMERIC);
echo 'Sort Array<int> Time: '. round(microtime(true) - $time, 8) . " secs\n";



$obj = new StdVector(TYPE_SCALAR_INT);
for ($i =0; $i < $limit; $i++) {
    $obj->push(mt_rand(0, $limit));
}
$time = microtime(true);
for ($i =0; $i < $limit; $i++) {
    $value = $obj->at($i);
}
echo 'Access element in StdVector<int> Time: '. round(microtime(true) - $time, 40) . " secs\n";
$time = microtime(true);
$obj->sort();
echo 'Sort StdVector<int> Time: '. round(microtime(true) - $time, 8) . " secs\n";


// in_array  check performance on Object
$arr = array();
$search = new ABC($limit+1);
for ($i = 0; $i < $limit; $i++) {
    $arr[] = new ABC($i);
}
$arr[] = $search;
$time = microtime(true);
$pos = array_search($search, $arr, true);
echo 'search on Array<Object> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
$time = microtime(true);
$pos = array_search(new ABC(333), $arr, true);
echo 'search on Array<Object>(value unknown) Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($arr);


$obj = new StdVector(TYPE_COMPLEX_OBJECT);
for ($i = 0; $i < $limit; $i++) {
    $obj->push(new ABC($i));
}
$obj->push($search);
$time = microtime(true);
$pos = $obj->search($search);
echo 'search on StdVector<Object> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
$time = microtime(true);
$pos = $obj->search(new ABC(333));
echo 'search on StdVector<Object>(value unknown) Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($obj);