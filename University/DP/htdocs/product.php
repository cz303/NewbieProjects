<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body bgcolor="#FFFFFF">


<?php
if (isset($_GET['id'])){
require 'db_connect.php';
 
$db = new DB_CONNECT();


    $query = mysql_query("SELECT files.*,personal.name AS athor FROM files JOIN personal USING(user_id) WHERE files.id =".$_GET['id']."");
			
		$list = mysql_fetch_assoc($query);
		
		echo "<table cellpadding=10 cellspacing=5 align=center width=470>";
		echo "<tr><td><strong>Наименование:</strong> ".$list['name']."</td></tr>";
		echo "<tr><td><strong>Тип:</strong> ".$list['type']."</td></tr>";
		if($list['pic']==Null)
		echo "<tr><td align='center'><img src='/img/product/none.jpg' height=250 width='auto'/></td></tr>";
		else
		echo "<tr><td align='center'><img src='/files/".$list['folder']."/".$list['pic']."' height=250 width='auto'/></td></tr>";
		
        echo "<tr><td><strong>Добавил:</strong> ".$list['athor']."</td></tr>";
		echo "<tr><td><strong>Дата добавления:</strong> ".$list['added']."</td></tr>";
		echo "<tr><td><strong>Описание:</strong> ".$list['description']."</td></tr>";
		echo "<tr><td><a  href='/files/".$list['folder']."/".$list['file']."' target='_blank'>Скачать ".$list['name']."</a></td></tr>";

		echo "</table>";
}
?>


</body>



</html>