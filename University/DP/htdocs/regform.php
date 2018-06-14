<!doctype html>

<?php 
 if(!isset($_SESSION)){
 session_start(); }
if ( isset($_SESSION['user_id']) ) 
{
echo " <script> alert('Вы уже авторизованны'); </script>";
 exit();
} 
require 'db_connect.php';
$db = new DB_CONNECT();
?>

<html>
<head>
<meta charset="utf-8">

<style type="text/css">
input {
    outline:none;
}
.invalid {
    background: rgba(255, 0, 0, 0.4);
}
.error{
    position: absolute;
    text-align: center;
//    line-height: 30px;
	  color:red;
//    margin-left: 10px;
//    display: inline-block;
    vertical-align: top;
}

.error::before{
    width: 13px;
    height: 6px;
    position: absolute;
    top: 8px;
    left: -10px;
}

input[type="text"], input[type="password"] {
    -moz-border-radius-topleft: 30px;
    -webkit-border-top-left-radius: 30px;
    border-top-left-radius: 30px;
    -moz-border-radius-bottomleft: 30px;
    -webkit-border-bottom-left-radius: 30px;
    border-radius: 30px;
    border: 1px solid #848484;
    outline:0; 
    height:20px;  
    padding-left:10px;
}
input[type="text"]:focus, input[type="password"]:focus {
	padding: 3px 8px 3px 8px;
	font-weight: bold;
	background-color: #C4C9E5
	-webkit-box-shadow: 2px 2px 15px;
	box-shadow: 2px 2px 15px;
}
</style>

<script type="text/javascript" src="./js/jquery1.10.min.js"></script>
<script type="text/javascript" src="./jQueryAssets/jquery-ui-1.8.14.custom.min.js"></script>
<script type="text/javascript" src="./jQueryAssets/jquery.form.js"></script>
<script type="text/javascript" src="./js/jquery.form.validation.js"></script>
<link href="./jQueryAssets/jquery-ui-1.8.14.custom.css" rel="stylesheet" type="text/css" />
</head>
<script type="text/javascript">
function ajax() { //Ajax отправка формы
    var msg = $("form").serialize();
    $.ajax({
        type: "POST",
        url: "./regform.php",
        data: msg,
        success: function (data) {
		   $("#results").html(data);
		   $('#regform').hide();
		  // $("#results").html("Все окей");
        },
        error: function (xhr, str) {
            alert("Возникла ошибка!");
        },

    });
}

jQuery.fn.notExists = function () { //Проверка на существование элемента
    return $(this).length == 0;
}
		        
				
$(document).ready(function () { //Валидация формы
    $(".send").validation(
	 $(".login").validate({
		test:function(){
				if($(this).val().indexOf(' ') >= 0) return false;
				if($(this).val().length <= 0) return false;
				return true;
				},
		invalid: function () {
            if ($(this).nextAll(".error").notExists()) {
                $(this).after('<div class="error"> Введите корректный логин</div>');
                $(this).nextAll(".error").delay(3000).fadeOut("slow");
                setTimeout(function () {
                    $(".login").next(".error").remove();
                }, 4600);
            }
        },
        valid: function () {
            $(this).nextAll(".error").remove();
        }
    }),
	

	$(".pas").validate({
        test: "blank",
        invalid: function () {
            if ($(this).nextAll(".error").notExists()) {
                $(this).after('<div class="error"> Введите пароль</div>');
                $(this).nextAll(".error").delay(3500).fadeOut("slow");
                setTimeout(function () {
                    $(".pas").next(".error").remove();
                }, 4600);
            }
        },
        valid: function () {
            $(this).nextAll(".error").remove();
        }
    }),
	
	$('.pas2').validate({
		test: function(){
				return $(this).val() == $('.pas').val()
				},
	    invalid: function () {
            if ($(this).nextAll(".error").notExists()) {
                $(this).after('<div class="error"> Пароли не совпадают</div>');
                $(this).nextAll(".error").delay(3700).fadeOut("slow");
                setTimeout(function () {
                    $(".pas2").next(".error").remove();
                }, 4600);
            }
        },
        valid: function () {
            $(this).nextAll(".error").remove();
        }
	}),
	
    $(".name").validate({
        test: "blank letters",
        invalid: function () {
            if ($(this).nextAll(".error").notExists()) {
                $(this).after('<div class="error"> Введите корректное имя</div>');
                $(this).nextAll(".error").delay(3850).fadeOut("slow");
                setTimeout(function () {
                    $(".name").next(".error").remove();
                }, 4600);
            }
        },
        valid: function () {
            $(this).nextAll(".error").remove();
        }
    }),
	
    $(".email").validate({
        test: "blank email",
        invalid: function () {
            if ($(this).nextAll(".error").notExists()) {
                $(this).after('<div class="error"> Введите корректный email</div>');
                $(this).nextAll(".error").delay(4000).fadeOut("slow");
                setTimeout(function () {
                    $(".email").next(".error").remove();
                }, 4600);
            }
        },
        valid: function () {
            $(this).nextAll(".error").remove();
			}
        })
    );
});
// style="padding: 8px 8px 8px 40px;"
</script>

<body>

<?php
if ($_POST)
{
 $mess="";
 $query = mysql_query("SELECT * FROM users WHERE name='".$_POST['login']."'");
 $num = mysql_num_rows ($query);
if($num == 0){
if (isset($_POST['login']) ) $user_login = mysql_real_escape_string($_POST['login']);
if (isset($_POST['pas']) ) $user_pas = mysql_real_escape_string($_POST['pas']);
if (isset($_POST['name']) ) $user_name = mysql_real_escape_string($_POST['name']);
if (isset($_POST['email']) ) $user_email = mysql_real_escape_string($_POST['email']);
	
	$user_fav="";
	$query2 = mysql_query("SELECT * FROM category");
		while($list2 = mysql_fetch_assoc($query2))
		{  if(isset($_POST['chk'.$list2['id'].''])) $user_fav = $user_fav . $list2['id'] . ",";  }
		  
  
	$query = mysql_query(" INSERT INTO users  
		(name,pass,flag) 
		VALUES(\"".$user_login."\",
				\"".hash('sha256',$user_pas)."\",
				\"0\")
		");
	 $id = mysql_insert_id(); 

if($query && $id != 0){
	$query2=mysql_query(" INSERT INTO personal  
		(user_id,name,email,favotite) 
		VALUES(\"".$id."\",
				\"".$user_name."\",
				\"".$user_email."\",
				\"".$user_fav."\")
		");	

if($query2) { $mess = $mess . "<p style=\"color:red;\">Пользователь ".$user_name." успешно зарегистрирован в системе</p>";
		} else $mess = "<p style=\"color:red;\">Какая-то ошибка 1</p>";
		}
        else $mess = "<p style=\"color:red;\">Какая-то ошибка 2</p>";
}
else $mess = $mess . "<p style=\"color:red;\">Пользователь ".$_POST['login']." уже зарегистрирован в системе, укажите другой логин.</p> 
								<br><a href='regform.php'>Вернуться</a>";
		
echo ($mess);	  
		
}
else{
echo('
<div id="regform">
        <form id="form" name="form" method="post" action="javascript:void(0);" onsubmit="ajax()">
            Ваш логин:
            <br><input type="text" name="login" size="25" class="login" value="" /> <p></p>
			Пароль:
            <br><input type="password" name="pas" size="25" class="pas" value="" /><p></p>
			Введите пароль повторно:
            <br><input type="password" name="pas2" size="25" class="pas2" value="" /><p></p>
			Ваше имя:
            <br><input type="text" name="name" size="25" class="name" value="" /><p></p>
         	Ваш email:
            <br><input type="text" name="email" size="25" class="email" value="" /><p></p>
            <p>Интересующие категории:</p>');
            
			
			$query2 = mysql_query("SELECT * FROM category");
			  while($list2 = mysql_fetch_assoc($query2))
			  {
			  echo(' <label><input type="checkbox" name="chk'.$list2['id'].'"'); 
			  echo('/>'.$list2['name'].'</label><br> ');
			  }
			
			
			
 echo('           <p><br><center><input type="submit" name="send" class="send" value="Зарегистрироваться"></center></p>
        </form></div>');
}
?>

<div id="results"></div>
</body>


</html>