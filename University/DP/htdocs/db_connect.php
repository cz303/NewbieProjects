<?php
 
class DB_CONNECT {
 
    function __construct() {
        $this->connect();
    }
 
    function __destruct() {
        $this->close();
    }
 
    function connect() {
        require 'db_config.php';
 
        $con = mysql_connect(DB_SERVER, DB_USER, DB_PASSWORD) or die(mysql_error());

        $db = mysql_select_db(DB_DATABASE) or die(mysql_error());
		
		mysql_query ("set_client='utf8'");
		mysql_query ("set character_set_results='utf8'");
		mysql_query ("set collation_connection='utf8_general_ci'");
		mysql_query ("SET NAMES utf8");

        return $con;
    }

    function close() {
        mysql_close();
    }
 
}
 
?>