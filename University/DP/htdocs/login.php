<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body bgcolor="#FFFFFF">
<?php session_start(); ?>


<?php

if (isset($_SESSION['user_id'])) 
{ } else {
require 'db_connect.php';
 
$db = new DB_CONNECT();

if (isset($_POST['lname']) && isset($_POST['pname']))
{
    $login = mysql_real_escape_string($_POST['lname']);
    $password = hash('sha256',$_POST['pname']);

    $query = "SELECT `users`.*,`personal`.`name` AS rname
            FROM `users` JOIN personal ON `users`.`id` = `personal`.`user_id`
            WHERE `users`.`name`='{$login}' AND `users`.`pass`='{$password}'
            LIMIT 1";
    $sql = mysql_query($query) or die(mysql_error());


    if (mysql_num_rows($sql) == 1) {

        $row = mysql_fetch_assoc($sql);
        $_SESSION['user_id'] = $row['id'];
		$_SESSION['user_flag'] = $row['flag'];
		$_SESSION['user_name'] = $row['rname'];
		$query = "SELECT `id` FROM `files` WHERE user_id=".$row['id']."";
		$sql = mysql_query($query) or die(mysql_error()); 
		$_SESSION['my_files'] = mysql_num_rows($sql);
		
		echo  "	 <script type=\"text/javascript\">
				 parent.window.hs.close();
				  </script> ";
		echo  "	 <script type=\"text/javascript\"> parent.window.location.reload(); </script> ";
    }
    else {
        echo "Такой логин с паролем не найдены в базе данных.";
		echo "<br><a href='/loginform.php'>Вернуться</a>";
    }
}
}
?>

</body>
</html>