<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body>
<?php
$title="SHOPITO - Обратная связь";
?>
<form action="mailto:admin@educloud.ru" enctype="text/plain" method="post"  style="margin: 0 auto; width:450px;">
			<input TYPE="hidden" NAME="VTI-GROUP" VALUE="0">
			<p><strong>Тип отправляемого сообщения:</strong></p>
			<dl>
				<dd><input type="radio" name="MessageType" value="Жалоба">Жалоба
				<input type="radio" checked name="MessageType" value="Вопрос">Вопрос
				<input type="radio" name="MessageType" value="Предложение">Предложение
				<input type="radio" name="MessageType" value="Благодарность">Благодарность</dd>
			</dl>
			<p><strong>Тема&nbsp; </strong></p>
			<blockquote>
				<p><input type="text" size="26" maxlength="256" name="Subject"></p>
			</blockquote>
			<p><strong>Введите текст сообщения в следующее поле:</strong></p>
			<dl>
				<dd><textarea name="Заметки" rows="5" cols="52"></textarea></dd>
			</dl>
			<p><strong>Как с вами связаться?</strong></p>
			<dl>
				<dd>
				<table>
					<tr>
						<td>Имя</td>
						<td>
						<input type="text" size="35" maxlength="256" name="Username"></td>
					</tr>
					<tr>
						<td>Эл. адрес</td>
						<td>
						<input type="text" size="35" maxlength="256" name="UserEmail"></td>
					</tr>
					<tr>
						<td>Телефон</td>
						<td>
						<input type="text" size="35" maxlength="256" name="UserTel"></td>
					</tr>
					<tr>
						<td>Факс</td>
						<td>
						<input type="text" size="35" maxlength="256" name="UserFAX"></td>
					</tr>
				</table>
				</dd>
			</dl>
			<p align="center"><input type="submit" value="Отправить">
			<input type="reset" value="Очистить форму"></p>
		</form>
      
</body>



</html>