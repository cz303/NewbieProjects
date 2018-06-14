<?php
 
$response = array();

require 'db_connect.php';
 
$db = new DB_CONNECT();
 
$result = mysql_query("SELECT * FROM category") or die(mysql_error());
 
if (mysql_num_rows($result) > 0) {
    $response["category"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        $cat = array();
        $cat["id"] = $row["id"];
        $cat["name"] = $row["name"];
        $cat["des"] = $row["description"];
 
        array_push($response["category"], $cat);
    }
    $response["success"] = 1;
 
    echo json_encode($response);
} else {
    $response["success"] = 0;
    $response["message"] = "Не найдено категорий";
 
    echo json_encode($response);
}
?>