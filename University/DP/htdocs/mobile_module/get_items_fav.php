<?php
 
$response = array();

require 'db_connect.php';
 
$db = new DB_CONNECT();
 
 if (isset($_POST['login'])) {
 
$login = $_POST['login'];
 
$result = mysql_query("SELECT id FROM users WHERE name='$login'") or die(mysql_error());
$row = mysql_fetch_array($result);
$id = $row["id"];
$result = mysql_query("SELECT personal.favotite FROM personal WHERE user_id=$id") or die(mysql_error());
$row = mysql_fetch_array($result);
$array = split(',',$row['favotite']);
$query_parts = array();
 foreach ($array as $val) {
    if($val!="") $query_parts[] = "'%".$val."%'";
}
$string = implode(' OR cat_id LIKE ', $query_parts);

$result = mysql_query("SELECT files.* FROM files WHERE cat_id LIKE {$string} ORDER by added DESC") or die(mysql_error());

if (mysql_num_rows($result) > 0) {
    $response["items"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        $cat = array();
        $cat["id"] = $row["id"];
        $cat["name"] = $row["name"];
		$cat["added"] = $row["added"];
 
        array_push($response["items"], $cat);
    }
    $response["success"] = 1;
 
    echo json_encode($response);
} else {
    $response["success"] = 0;
    $response["message"] = "Не найдено избранных материалов";
 
    echo json_encode($response);
}
}
else {
        $response["success"] = 2;
        $response["message"] = "POST отсуствует";
 
        echo json_encode($response);
    }
?>