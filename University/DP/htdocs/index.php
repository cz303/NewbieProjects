<!doctype html>
<html>
<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type">
<link rel="icon" href="img/fav.png" type="image/x-icon">

<link rel="stylesheet" href="./css/style.css"	   media="screen" type="text/css">
<link rel="stylesheet" type="text/css" href="/js/highslide/highslide.css" />

<script type="text/javascript" src="/js/highslide/highslide-full.js"></script>
<script src="/jQueryAssets/jquery-1.8.3.min.js" type="text/javascript"></script>

<script type="text/javascript">
$(document).ready(function(){
    $('.css-menu-1 li a').each(function(index) {
        if(this.href.trim() == window.location)
            $(this).addClass("selected");
    });
});
</script>

 <script type="text/javascript">
	hs.graphicsDir = '/js/highslide/graphics/';
	hs.align = 'center';
	hs.transitions = ['expand'];
	hs.fadeInOut = true;	
	hs.outlineType = 'rounded-white';
	hs.preserveContent = false;
	hs.loadingOpacity = 1;
	hs.cacheAjax = false;
	hs.dimmingOpacity = .75;
	hs.fullExpandOpacity = 1;
	hs.showCredits = false;
	hs.wrapperClassName = 'draggable-header';
</script>

</head>

<body>

<?php
 if(!isset($_SESSION)){
 session_start(); }
	if (isset($_GET['exit'])){
     session_destroy();
	 header('Location: index.php'); exit();
	}
?>

<aside style="z-index: 0; padding-right: 10px; border-radius: 10px; -webkit-box-shadow: 2px 1px 10px 0px; box-shadow: 2px 1px 10px 0px; right: 7px; padding-bottom: 0.5px; padding-top: 0.5px; float: right; left: 100px; margin-left: 0px; min-width: 150px;">
  <h4 style="text-align:center;">Помощь<br>консультанта </h4>
  <p style="text-align: center;" > <font style="color: rgba(189,189,189,1.00); font-size: 14px; position: relative;
top: -.2ex; padding-right: .3ex;">(495)</font><font style="color:rgba(248,128,71,1.00); font-weight:bold; font-size: 18px; text-align:center;">333-33-33</font> <br>
    <font style="text-align:center;"> Ежедневно <br>с 10:00 до 22:00</font> </p>
  <p style="text-align:right;"> <a href="index.php?content=callback">Обратная связь</a> </p>
</aside>
<div class="sbody" >
  <div >
    <div class="header">
      <table width="100%" border="0">
        <tr>
          <td width="400"></td>
          <td>
				<img src="img/mirea.jpg" width=100>
          </td>
          <td><div class="header_t">
           
         <?php

		  if (isset($_SESSION['user_id'])) 
			{
		  echo ("Добро пожаловать ".$_SESSION['user_name']."! <br>");
		  if ($_SESSION['user_flag'] == 1) {echo ("Вы администратор.<br>");}
		  echo ("<br><a href='personal.php' onclick=\"return hs.htmlExpand(this, 
				{ objectType: 'iframe', width:370,height:500, headingText:'Личный кабинет'} )\">Личный кабинет</a>");
		  echo ('<br>Количество добавленных материалов: <a href="index.php?content=trade_content&my_files" >'.$_SESSION['my_files'].'<br>');
		  echo ("<br> <a href='index.php?exit=1'>Выход</a><br>");	
			}
			else {
		echo("Для получения каких либо возможностей, <br>требуется авторизация! <br>");
		echo("<br>"); 
				echo ("<a href='/loginform.php' 
				onclick=\"return hs.htmlExpand(this, 
				{ objectType: 'iframe', width:250,height:150, headingText:'Форма авторизации'} )\">
				Вход</a><br>");
				echo("<a href='regform.php' onclick=\"return hs.htmlExpand(this, 
				{ objectType: 'iframe', width:280,height:600, headingText:'Форма регистрации'} )\">Регистрация</a>");
				
				}
				
         ?>          
          </div>
          </td>
        </tr>
      </table>
    </div>
   </div>
    
    <div class="menu">
      <ul class="css-menu-1">
        <li ><a href="index.php?content=hello">Новости</a></li>
        <li ><a href="index.php?content=trade">Образование</a></li>
        <li ><a href="index.php?content=map">Карта сайта</a></li>
        <li ><a href="index.php?content=about">О нас</a></li>
      </ul>
    </div>
    
<div class="site_content">

<?php
// session_start(); 
if ( isset( $_GET['my_files'] ) ) 
{$my_files = 1;} else {$my_files = 0;}

if ( isset( $_POST['findText'] ) ) 
{
 $_SESSION['findText'] = $_POST['findText'];	
// header("Location: index.php?content=trade"); exit();
 include ("trade.php");
}
else {
if ( isset( $_GET['content'] ) && $_GET['content']!="") 
{ $content = $_GET['content']; }
else
{ 
header('Location: index.php?content=hello'); exit();
} 

include("$content.php"); 
}

?>
<title><?php echo $title; ?></title>
      
     
</div>
  

    
<div class="clear"> </div>   

  <div class="dop_info">
    <hr>
    <div class="social-btm"> <a href="https://vk.com/club11336495" target="_blank"><img width="32" height="32" src="/img/banner/vk_32.png" title="В Контакте"></a>  </div>
    <div class="copy"><span>©</span> 2013 EDUCLOUD</div>
    <div class="card"> </div>
  </div>
  

</div>



    
</body>
</html>