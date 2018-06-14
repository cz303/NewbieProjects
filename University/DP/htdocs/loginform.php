<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body bgcolor="#FFFFFF">
<script type="text/javascript">
function validateForm(loginForm)
{
var x=loginForm.lname.value;
var y=loginForm.pname.value;
var errors="";

if (x==null || x=="" || x.length <1)
  {
  errors+="Логин обязательно должен быть введен!\n";
  } 
if (y==null || y=="" || y.length <1)
  {
  errors+="Вы не указали пароль!";
  } 
  
if(errors=="")
return true;
else
{
alert(errors);
return false;
}
}
</script>

<?php
session_start();

if (isset($_SESSION['user_id'])) 
{
	echo "<a href='index.php?exit=1'>Выход</a>";	
}
else {

echo "
<form action=\"login.php\" name=\"loginForm\" onsubmit='return validateForm(this);' method=\"post\" >
    <table>
        <tr>
            <td>Логин:</td>
            <td><input type=\"text\" name=\"lname\" /></td>
        </tr>
        <tr>
            <td>Пароль:</td>
            <td><input type=\"password\" name=\"pname\"/></td>
        </tr>
        <tr>
            <td></td>
            <td><input type=\"submit\" value=\"Войти\" class=\"button\"/></td>
        </tr>
    </table>
</form>
";
}


?>

</body>
</html>