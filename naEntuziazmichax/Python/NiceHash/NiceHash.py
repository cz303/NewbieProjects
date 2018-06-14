import requests
import telebot
import sys

BTC_WALLET = ''
TOKEN = ''

URL_STATS = "https://api.nicehash.com/api?method=stats.provider&addr="+BTC_WALLET 
URL_WORKERS = "https://api.nicehash.com/api?method=stats.provider.workers&addr="+BTC_WALLET 
URL_PRICE = "https://api.bitfinex.com/v1/ticker/btcusd"
BTC_BALANCE = 'https://blockchain.info/q/addressbalance/'+BTC_WALLET 

""" 
Объект бота
"""
bot = telebot.TeleBot (TOKEN)

""" 
Наша клавиаутра с размером колонок в 2 элемента (row_width=2)
"""
keyboard = telebot.types.InlineKeyboardMarkup(row_width=2)
btn1 = telebot.types.InlineKeyboardButton(text="SCRYPT", callback_data="scrypt")
btn2 = telebot.types.InlineKeyboardButton(text="Баланс найсхеша", callback_data="balance")
btn3 = telebot.types.InlineKeyboardButton(text="SHA256", callback_data="sha256")
btn4 = telebot.types.InlineKeyboardButton(text="Equihash", callback_data="equihash")
btn5 = telebot.types.InlineKeyboardButton(text="Workers", callback_data="workers")
keyboard.add(btn1, btn2, btn3, btn4, btn5)

"""
Функция которая возвращает цену биткойна с биржи битфинекс
В ретурне возвращается как дробное число (float)
"""
def get_price():
	r = requests.get(URL_PRICE)
	response = r.json()
	return float(response['last_price'])


""" 
Функция которая ждет из чата команду /crypto
"""
@bot.message_handler(commands=['crypto'])
def send_welcome(message):
	balance = float(request_balance() / 100000000)
	msg = 'BTC: $'+ str(get_price()) + '\n'
	msg += 'Wallet balance: '+ str("{0:.5f}".format(balance)) + 'btc' + ' ($' + str(int(balance*get_price())) + ')' + '\n'
	msg += 'Выберите действие'
	bot.send_message (message.chat.id, msg, reply_markup=keyboard)

"""
Наша функция которая просто отправляет сообщение
по хендлеру (message)  и строку (msg), сообщение включает в себя
встроенную клавиатуру (reply_markup)
"""
def send_edit(message, msg):
	bot.send_message (message.chat.id, msg, reply_markup=keyboard)


"""
Мы знаем что массив воркеров у нас четко содержит либо цифры, либо USERS+цифра

Как устроен ответ API:
data                                - объект json ответа от API
data['result']['workers']           - в объекте ответа имеет вид списка (массива)
workers = data['result']['workers'] - копируем для удобства массив воркеров
workers[индекс]                     - элемент массива (1 воркер) от 0 до последнего индекса
workers[индекс][0]                  - Внутри элемента массива воркера тоже массив
									в его первом элементе [0] - Имя воркера
									во втором [1] - объект типа {'a': "100"} 
									поэтому чтобы получить значение поля с ключем 'a'
									обращаемся как workers[индекс][1]['a']
																		   
"""
def sort_workers(workers):
	numbers = []
	users = []

	""" Разделим массив на два, с цифрами и юзерами """
	for i in range( len( workers ) ):
		if "USER" not in workers[i][0]: 
			numbers.append(workers[i])
		if "USER" in workers[i][0]: 
			users.append(workers[i])

	""" 
	Потом каждый массив отсортируем по возрастанию
	сравнивая число в его имени и меняя местами элементы 
	( массив[номер элемента][0] - имя воркера )
	"""       
	for i in range( len( numbers ) - 1):
		for i2 in range(i+1, len( numbers ) ):
			if ( int(''.join(list(filter(str.isdigit, numbers[i][0])))) > int(''.join(list(filter(str.isdigit, numbers[i2][0])))) ):
				temp = numbers[i2]
				numbers[i2] = numbers[i]
				numbers[i] = temp

	for i in range( len( users ) - 1):
		for i2 in range(i+1, len( users ) ):
			if ( int(''.join(list(filter(str.isdigit, users[i][0])))) > int(''.join(list(filter(str.isdigit, users[i2][0])))) ):
				temp = users[i2]
				users[i2] = users[i]
				users[i] = temp    
	""" 
	Соединяем два отсортированных массива в один
	сначала добавляем масив с цифрами к мустому масиву, потом в конец добавляем каждый
	элемент из массива users (есть .extend(), чтобы без цикла, но хз как он сработает здесь)
	и возвращаем его в ретурн 
	"""
	result = numbers 
	for user in users:
		result.append(user)
	return result


""" 
Функция смотрит callback нажатой кнопки (пришедшего сообщения)
"""
@bot.callback_query_handler(func=lambda call: True)
def callback_inline(call):
	if call.message:
		try:
			if call.data == "scrypt":
				""" Получаем объект json данных с запроса """
				data = request_stats()
				""" Для удобства баланс в отдельную переменную рассчитываем """
				balance = float("{0:.5f}".format(float(data['result']['stats'][0]['balance'])))
				""" Получаем цену биткойна тоже в отдельную переменную """
				balance_usd = int(balance*get_price())
				""" Присваиваем в msg новую строку, а потом добавляем к этой строке еще две """
				msg = 'Ваш баланс SCRYPT: ' + str(balance) +' ($' + str( balance_usd )+')\n'
				msg += 'Не принятая скорость SCRYPT: '+ data['result']['stats'][0]['rejected_speed']+'\n'
				msg += 'Принятая скорость SCRYPT:'+ data['result']['stats'][0]['accepted_speed']
				""" Отсылаем сообщение в телегу через НАШУ функцию """
				send_edit(call.message, msg)
			elif call.data == "balance":
				data = request_stats()
				balance = float("{0:.5f}".format( float(data['result']['stats'][0]['balance']) + float(data['result']['stats'][1]['balance']) + float(data['result']['stats'][2]['balance']) ))
				balance_usd = int(balance*get_price())
				msg = 'Ваш общий баланс: '+ str(balance)+' ($' + str(balance_usd)+')\n'
				msg += 'Последняя выплата:\n' + data['result']['payments'][0]['time'] + '\n' + data['result']['payments'][0]['amount'] + 'btc'
				send_edit(call.message, msg)
			elif call.data == "sha256":
				data = request_stats()
				balance = float("{0:.5f}".format(float(data['result']['stats'][1]['balance'])))
				balance_usd = int(balance*get_price())
				msg = 'Ваш баланс SHA256:' + str(balance) +' ($' + str(balance_usd) + ')\n'
				msg += 'Не принятая скорость SHA256: '+ data['result']['stats'][1]['rejected_speed']+'\n'
				msg += 'Принятая скорость SHA256:'+ data['result']['stats'][1]['accepted_speed']
				send_edit(call.message, msg)
			elif call.data == "equihash":
				data = request_stats()
				balance = float("{0:.5f}".format(float(data['result']['stats'][2]['balance'])))
				balance_usd = int(balance*get_price())
				msg = 'Ваш баланс Equihash: ' + str(balance) +' ($' + str( balance_usd ) + ')\n'
				msg += 'Не принятая скорость Equihash: '+ data['result']['stats'][2]['rejected_speed']+'\n'
				msg += 'Принятая скорость Equihash:'+ str(float(data['result']['stats'][2]['accepted_speed']) * 1000000)
				send_edit(call.message, msg)
			elif call.data == "workers":
				data = request_workers()
				workers = sort_workers(data['result']['workers'])          
				msg = 'Воркеров в сети: '+ str(len(workers)) + '\n'
				""" Для каждого элемента массива workers выводим его имя и хешрейт """
				for i in range( len( workers ) ):
					msg += 'Имя: ' + workers[i][0] + ' Хешрейт: ' + workers[i][1]['a'] + '\n'
				send_edit(call.message, msg)

		except:
			""" Если в выполнении куска кода выше произошла ошибка - то пришлем просто ошибку"""
			bot.send_message(call.message.chat.id, 'Ошибка\n' + repr(sys.exc_info())) 
			"""
			А в консоль напишем тип ошибки и её текст 
			Получится вроде -
				ТипОшибки("текст ошибки",)
			"""
			print(repr(sys.exc_info()))
		
def request_stats():
	r = requests.get(url = URL_STATS)
	data = r.json()
	return data

def request_workers():
	r = requests.get(url = URL_WORKERS)
	data = r.json()
	return data

def request_balance():
	r = requests.get(url = BTC_BALANCE)
	data = r.json()
	return data

""" 
Этот код выполняется один раз при запуске
и устанавливает бота работать в бесконечном режиме опроса телеги
"""
if __name__ == '__main__':
	bot.polling(none_stop=True)