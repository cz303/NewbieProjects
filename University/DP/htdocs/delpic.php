<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body>


<?php 
session_start();
if ( !isset($_SESSION['user_id']) ) 
{
echo " <script> alert('Вы не авторизованы как администратор'); </script>";
header('HTTP/1.0 401 Unauthorized');
}

if( isset( $_GET['id'] ))
{
require 'db_connect.php';
$db = new DB_CONNECT();


	$query = mysql_query("SELECT * FROM files WHERE id =".$_GET['id']." ");
	$num = mysql_num_rows ($query);
	if($num > 0)
	{ $list = mysql_fetch_assoc($query);
	if($list['pic'] != NULL) unlink("./files/".$list['folder']."/".$list['pic']."");
	mysql_query("UPDATE files SET pic=NULL WHERE id = ".$_GET['id']."");
	echo "Изображение удалено! <br>"; 
	}
	
}
echo "<a href=\"edit.php?id=".$_GET['id']."\">Вернуться обратно</a>";
?>

</body>



</html>