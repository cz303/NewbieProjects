<!doctype html>
<html>
<head>
<meta charset="utf-8">

</head>

<body bgcolor="#FFFFFF">

<?php
session_start();
if ( !isset($_SESSION['user_id']) && $_SESSION['user_flag'] != 1) 
{
echo " <script> alert('Вы не авторизованы как администратор'); </script>";
header('HTTP/1.0 401 Unauthorized'); exit();
}

function deleteDirectory($dir) {
    if (!file_exists($dir)) return true;
    if (!is_dir($dir)) return unlink($dir);
    foreach (scandir($dir) as $item) {
        if ($item == '.' || $item == '..') continue;
        if (!deleteDirectory($dir.DIRECTORY_SEPARATOR.$item)) return false;
    }
    return rmdir($dir);
}

require 'db_connect.php';
$db = new DB_CONNECT();

if ( isset( $_GET['del']  ) )
{
	$query = mysql_query("SELECT * FROM files WHERE cat_id =".$_GET['del']." ");
	$num = mysql_num_rows ($query);
	if($num > 0)
	{
	while($list = mysql_fetch_assoc($query)) {
	mysql_query("DELETE FROM files WHERE id = ".$_GET['del']."");
	deleteDirectory("./files/".$list['folder']."");
	echo "".$list['name']." удален!<br>";
		}
	}
	else {
	echo " Записей в данной категории нету <br>";
	}
	$query = mysql_query("DELETE FROM `edubase`.`category` WHERE `category`.`id` =".$_GET['del']." ");
	if($query) echo "Категория удалена";
	else echo "Ошибка удаления категории";
}

?>

</body>
</html>