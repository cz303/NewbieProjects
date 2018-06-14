<?php
 
$response = array();

require 'db_connect.php';
 
$db = new DB_CONNECT();
 
 if (isset($_POST['id'])) {
 
$id = $_POST['id'];
 
$result = mysql_query("SELECT files.*,personal.name AS at FROM files JOIN personal USING(user_id) WHERE id=$id") or die(mysql_error());
 
if (mysql_num_rows($result) > 0) {
    $response["item"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        $cat = array();
        $cat["id"] = $row["id"];
        $cat["name"] = $row["name"];
		$cat["description"] = $row["description"];
        $cat["type"] = $row["type"];
		$cat["added"] = $row["added"];
        $cat["at"] = $row["at"];
		$cat["id"] = $row["id"];
        $cat["folder"] = $row["folder"];
		if($row["pic"]!="")	{$cat["pic"] = $row["pic"];}	else {$cat["pic"] = "NULL";}
        $cat["file"] = $row["file"];
		
        array_push($response["item"], $cat);
    }
    $response["success"] = 1;
 
    echo json_encode($response);
} else {
    $response["success"] = 0;
    $response["message"] = "Не найдено материала с этим ID=$id";
 
    echo json_encode($response);
}
}
else {
        $response["success"] = 2;
        $response["message"] = "POST отсуствует";
 
        echo json_encode($response);
    }
?>