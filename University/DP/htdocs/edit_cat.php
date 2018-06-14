<!doctype html>
<html>
<head>
<meta charset="utf-8">

<script type="text/javascript" src="jQueryAssets/jquery-1.6.2.min.js"></script>
<script type="text/javascript" src="jQueryAssets/jquery-ui-1.8.14.custom.min.js"></script>
<script type="text/javascript" src="jQueryAssets/jquery.form.js"></script>
<link href="jQueryAssets/jquery-ui-1.8.14.custom.css" rel="stylesheet" type="text/css" />


</head>

<body bgcolor="#FFFFFF">

<?php
session_start();
if ( !isset($_SESSION['user_id']) && $_SESSION['user_flag'] != 1) 
{
echo " <script> alert('Вы не авторизованы как администратор'); </script>";
header('HTTP/1.0 401 Unauthorized'); exit();
}

if ($_POST)
{
   	require 'db_connect.php';
	$db = new DB_CONNECT();
	$mess="";
	
	if (isset($_POST['name']) ) $cat_name = mysql_real_escape_string($_POST['name']);
	if (isset($_POST['des']) ) $cat_des = mysql_real_escape_string($_POST['des']);
	  
		  
$query = mysql_query('UPDATE category SET name="'.$cat_name.'", description="'.$cat_des.'" WHERE id="'.$_POST['id'].'"');
	
			if($query) { 
					$mess = $mess . '<p style=\"color:red;\">Запись <b>'.$_POST['name'].'</b> успешно отредактированна.</p>';
					}
				else $mess = "<p style=\"color:red;\">Какая-то ошибка.</p>";
		 
		 echo ($mess);

 } 
		
		
if (!$_POST)
{
require 'db_connect.php';
$db = new DB_CONNECT();
$query = mysql_query("SELECT * FROM category WHERE id=".$_GET['id']." ");
$num = mysql_num_rows ($query);
	if($num > 0)
	{
		$list = mysql_fetch_assoc($query);
		echo ('

		<form name="add"  id="add" method="post" action="'.$_SERVER['PHP_SELF'].'" enctype="multipart/form-data" >
		   Наименование: <br>
		  <input type="text" name="name" size="100" id="name" value="'.$list['name'].'" style="width: 300px;"/>
		  <p> Описание: <br>
			<textarea type="text" name="des" id="des" style="width: 300px; height: 70px;">'.$list['description'].'</textarea>
			<input type="hidden" name="id" value="'.$_GET['id'].'" />
			<p style="text-align: center;">
			<input type="submit" name="add_btm" id="add_btm"  value="Сохранить" 
			onclick = "this.style.visibility=hidden" />
		</form>

		');
	}

}
?>

</body>
</html>