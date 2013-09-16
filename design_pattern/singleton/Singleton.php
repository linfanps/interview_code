<?php
class Singleton 
{
    private static $_instance;
    private function __construct()
    {
        echo "Singleton is constructed\n";
    }
    
    public static function getInstance() 
    {
        if (!isset($_instance)) {
            $_instance = new Singleton();
        }
        return $_instance;
    }

    public function __clone()
    {
        trigger_error("can not clone", E_USER_ERROR);
    }
    
    public function test() 
    {
        echo "test\n";
    }
}

$s = Singleton::getInstance();
$s->test();
//$s1 = clone $s;
//$test = new Singleton();




