/* 
TODO:
typing box
color avatar (select color) (fa font) + hint + text
back + clear local storage
*/
var Chat = document.getElementById("chat");
var LoginForm = document.getElementById("login");
var SendForm = document.getElementById("send");
var chatPage = document.getElementById("chat_page");

var userLogin;
var messages = [];

function init() {
  LoginForm.addEventListener("submit", login);
  SendForm.addEventListener("submit", send);
  SendForm.addEventListener("keypress", sendByEnter);

  document.getElementById("back").addEventListener("click", back);
  document.getElementById("menu").addEventListener("click", clear);

  try {
    userLogin = localStorage.getItem("login");
  } catch (err) {
    console.log(err);
  }

  if (userLogin == "" || userLogin == null) {
    Chat.dataset.page = "login";
  } else {
    Chat.dataset.page = "chat";
    loadMessages();
  }
}

init();

function back() {
  userLogin = "";
  localStorage.removeItem("login");
  while (chat_page.firstChild) {
    chat_page.removeChild(chat_page.firstChild);
  }
  init();
}

function clear() {
  localStorage.clear();
  messages = [];
  while (chat_page.firstChild) {
    chat_page.removeChild(chat_page.firstChild);
  }
  init();
}

function loadMessages() {
  if (localStorage["messages"] != null) {
    messages = JSON.parse(localStorage["messages"]);
    messages.forEach(elem => {
      addMessage(elem, false);
    });
  } else {
    localStorage.setItem("messages", JSON.stringify(messages));
  }

  chatPage.scrollTop = chatPage.scrollHeight;
}

/**
 * @param {Event | HTMLFormElement} e
 * @return {boolean}
 */
function login(e) {
  e.preventDefault();
  userLogin = document.getElementById("username").value;

  if (userLogin != "") {
    localStorage.setItem("login", userLogin);
    Chat.dataset.page = "chat";
    loadMessages();
  }
}

/**
 * @param {Event | HTMLFormElement} e
 * @return {boolean}
 */

function sendByEnter(e) {
    var key = e.which || e.keyCode;
    if (key === 13) {
      send(e);
      return;
    }
}

function send(e) {
  e.preventDefault();

  var message = SendForm.querySelector("textarea");
  const regex = /^!test\s/i;

  if (regex.test(message.value)) {
    messages.push({
      id: 123,
      user: "Test",
      msg: message.value.replace(regex, ""),
      date: Date.now()
    });
    localStorage.setItem("messages", JSON.stringify(messages));
    addMessage(messages[messages.length - 1], true);

    message.value = "";
  }

  if (message.value != "") {
    messages.push({
      id: 123,
      user: userLogin,
      msg: message.value,
      date: Date.now()
    });
    localStorage.setItem("messages", JSON.stringify(messages));
    addMessage(messages[messages.length - 1], true);

    message.value = "";
  }

  chatPage.scrollTop = chatPage.scrollHeight;
}

function addMessage(user, animate) {
  var itm = document.getElementById("example");
  var cln = itm.cloneNode(true);
  cln.setAttribute("id", "m" + user.id);
  cln.querySelector(".avatar").setAttribute("title", user.user);
  cln.querySelector(".messageBox").dataset.from = user.user;
  cln.querySelector(".mTime").innerHTML = user.user;
  if (user.user == userLogin)
    cln.querySelector(".messageBox").dataset.style = "self";
  else cln.querySelector(".messageBox").dataset.style = "comrade";
  cln.querySelector(".mText").innerHTML = user.msg;
  if (animate) {
    cln.querySelector(".messageBox").classList.add("animate");
  }

  document.getElementById("chat_page").appendChild(cln);
}
