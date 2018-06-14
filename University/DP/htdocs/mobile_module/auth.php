<?php
 
$response = array();

require 'db_connect.php';
$db = new DB_CONNECT();
 
// require_once("json_encode.php");
 
if (isset($_POST['login']) && isset($_POST['pas'])) {
    $login = $_POST['login'];
	$pas = hash('sha256',$_POST['pas']);
	
    $result = mysql_query("SELECT * FROM users WHERE name = '".$login."' and pass = '".$pas."'");
	
    if (!empty($result)) {
	  if (mysql_num_rows($result) > 0) {
            $response["success"] = 1;
			$response["message"] = "Вход пыполнен";
			
			echo json_encode($response);
        
		}else {
            $response["success"] = 3;
            $response["message"] = "Не найдена комбинация логина пароля";
 
            echo json_encode($response);
			} 
	}
	else {
        $response["success"] = 4;
        $response["message"] = "Ошибка в запросе";
 
        echo json_encode($response);
    }
}
else {
        $response["success"] = 5;
        $response["message"] = "POST отсутствует";
 
        echo json_encode($response);
    }
?>