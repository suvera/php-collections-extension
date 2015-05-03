<?php
$time = microtime(true);
$arr = array();
for ($i =0; $i < 1000000; $i++) {
    $arr['key'.$i] = $i;
}
unset($arr);
echo 'Array<String, Int> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";

/*
$time = microtime(true);
$arr = new ArrayObject();
for ($i =0; $i < 1000000; $i++) {
    $arr->offsetSet('key'.$i, $i);
}
unset($arr);
echo 'ArrayObject<String, Int> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";
*/

$time = microtime(true);
$obj = new StdMap(TYPE_SCALAR_INT, 1000000);
for ($i =0; $i < 1000000; $i++) {
    $obj->push('key'.$i, $i);
}
unset($obj);
echo 'StdMap<String, Int> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


// in_array  check performance on Int
$arr = array();
for ($i =0; $i < 1000000; $i++) {
    $arr['key'.$i] = $i;
}
$time = microtime(true);
$pos = array_search(500000, $arr);
echo 'search on Array<String, Int> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($arr);


$obj = new StdMap(TYPE_SCALAR_INT, 1000000);
for ($i =0; $i < 1000000; $i++) {
    $obj->push('key'.$i, $i);
}
$time = microtime(true);
$pos = $obj->search(500000);
echo 'search on StdMap<String, Int> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
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
for ($i =0; $i < 1000000; $i++) {
    $arr['key'.$i] = new ABC($i);
}
unset($arr);
echo 'Array<String, Object> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";


$time = microtime(true);
$obj = new StdMap(TYPE_COMPLEX_OBJECT, 1000000);
for ($i =0; $i < 1000000; $i++) {
    $obj->push('key'.$i, new ABC($i));
}
unset($obj);
echo 'StdMap<String, Object> creation Time: '. round(microtime(true) - $time, 8) . " secs\n";



// sorting
$arr = array();
for ($i =0; $i < 1000000; $i++) {
    $arr['key'.$i] = mt_rand(0, 1000000);
}
$time = microtime(true);
for ($i =0; $i < 1000000; $i++) {
    $value = $arr['key'.$i];
}
echo 'Access element in Array<String, Int> Time: '. round(microtime(true) - $time, 40) . " secs\n";

$obj = new StdMap(TYPE_SCALAR_INT, 1000000);
for ($i =0; $i < 1000000; $i++) {
    $obj->push('key'.$i, mt_rand(0, 1000000));
}
$time = microtime(true);
for ($i =0; $i < 1000000; $i++) {
    $value = $obj->at('key'.$i);
}
echo 'Access element in StdMap<String, Int> Time: '. round(microtime(true) - $time, 40) . " secs\n";

// Array keys
$time = microtime(true);
$keys = array_keys($arr);
echo 'array_keys Array<String, Int> Time: '. round(microtime(true) - $time, 8) . " secs\n";

$time = microtime(true);
$keyObk = $obj->keys();
echo 'getKeys StdMap<String, Int> Time: '. round(microtime(true) - $time, 8) . " secs\n";


// in_array  check performance on Object
$arr = array();
$search = new ABC(1000001);
for ($i = 0; $i < 1000000; $i++) {
    $arr['key'.$i] = new ABC($i);
}
$arr['key1000001'] = $search;
$time = microtime(true);
$pos = array_search($search, $arr, true);
echo 'search on Array<String, Object> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
$time = microtime(true);
$pos = array_search(new ABC(333), $arr, true);
echo 'search on Array<String, Object>(value unknown) Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($arr);


$obj = new StdMap(TYPE_COMPLEX_OBJECT, 1000000);
for ($i = 0; $i < 1000000; $i++) {
    $obj->push('key'.$i, new ABC($i));
}
$obj->push('key1000001', $search);
$time = microtime(true);
$pos = $obj->search($search);
echo 'search on StdMap<String, Object> Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
$time = microtime(true);
$pos = $obj->search(new ABC(333));
echo 'search on StdMap<String, Object>(value unknown) Time: '. round(microtime(true) - $time, 8) . " secs ($pos)\n";
unset($obj);
