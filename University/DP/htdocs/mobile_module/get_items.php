<?php
 
$response = array();

require 'db_connect.php';
 
$db = new DB_CONNECT();
 
 if (isset($_POST['id'])) {
 
$id = $_POST['id'];
 
$result = mysql_query("SELECT * FROM files WHERE cat_id=$id") or die(mysql_error());
 
if (mysql_num_rows($result) > 0) {
    $response["items"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        $cat = array();
        $cat["id"] = $row["id"];
        $cat["name"] = $row["name"];
 
        array_push($response["items"], $cat);
    }
    $response["success"] = 1;
 
    echo json_encode($response);
} else {
    $response["success"] = 0;
    $response["message"] = "Не найдено материалов в этой категории";
 
    echo json_encode($response);
}
}
else {
        $response["success"] = 2;
        $response["message"] = "POST отсуствует";
 
        echo json_encode($response);
    }
?>