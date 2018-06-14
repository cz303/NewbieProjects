'use strict'

var game = null;

// Конструктор для объекта игры
function GameConstructor(time, emoji) {
    this.compareRandom = function (a, b) {
        return Math.random() - 0.5;
    }

    // Для случайного расположения эмоджи
    this.orders = [1, 2, 5, 2, 1, 3, 6, 4, 4, 5, 3, 6].sort(this.compareRandom);
    this.items = emoji.sort(this.compareRandom).slice(0, 6);

    this.found = 0;
    this.seek = null;
    this.fail = null;
    this.inProgress = false;
    this.remaining = time;
    this.timer = null;

    // Вызывается при клике на карту 
    this.compare = function (card) {
        if (card != this.seek && card != this.fail) {
            card.classList.toggle("flip");

            if (this.fail) {
                this.toggleClass([this.seek, this.fail], 'fail');
                this.toggleClass([this.seek, this.fail], 'flip');
                this.fail = null;
                this.seek = null;
            }

            if (this.seek == null) {
                this.seek = card;
            } else {
                if (this.seek.dataset.index == card.dataset.index) {
                    this.toggleClass([this.seek, card], 'success');
                    this.seek.removeEventListener('click', flipCard);
                    card.removeEventListener('click', flipCard);
                    this.seek = null;
                    this.found += 1;
                    if (this.found == 6)
                        this.stop();
                } else {
                    this.toggleClass([this.seek, card], 'fail');
                    this.fail = card;
                }
            }

        }
    }

    // Запуск новой игры
    this.start = function () {
        this.inProgress = true;
        Array.from(document.querySelectorAll('.card')).forEach(function (elem, index) {
            elem.querySelector('.back').textContent = game.items[game.orders[index] - 1];
            elem.dataset.index = game.orders[index];
        });

        this.remaining--;
        document.querySelector('#timer').innerHTML = this.formatTime(this.remaining);

        function countdown() {
            this.remaining--;
            document.querySelector('#timer').innerHTML = this.formatTime(this.remaining);
            if (this.remaining < 1)
                this.stop();
        }

        this.timer = setInterval(countdown.bind(this), 1000);
    }

    // Остановка игры
    this.stop = function () {
        clearInterval(this.timer);
        document.querySelector('#popup').classList.remove('hidden');
        if (this.seek == null && this.found == 6) {
            document.querySelector('.win').classList.remove('hidden');
            document.querySelector('.button').innerHTML = 'Play again';
        } else {
            document.querySelector('.lose').classList.remove('hidden');
            document.querySelector('.button').innerHTML = 'Try again';
        }
    }

    this.formatTime = function (sec) {
        var minutes = Math.floor(sec / 60);
        var seconds = (sec - minutes * 60);
        if (minutes < 10) {
            minutes = "0" + minutes;
        }
        if (seconds < 10) {
            seconds = "0" + seconds;
        }
        return minutes + ':' + seconds;
    }

    this.toggleClass = function (item, className) {
        item.forEach(element => {
            element.classList.toggle(className);
        });
    }
}

// Клик по карте
function flipCard(event) {
    if (!game.inProgress) {
        game.start();
    }
    game.compare(this);
}

// Спрятать модальное окно
function hidePopup() {
    document.querySelector('#popup').classList.add('hidden');
    document.querySelector('.win').classList.add('hidden');
    document.querySelector('.lose').classList.add('hidden');
}

// Создать объект и обнулить поле 
function newGame() {
    game = new GameConstructor(60, ['🐶', '🐱', '🐭', '🐹', '🐰', '🐻', '🐼', '🐨', '🐯', '🦁', '🐮', '🐷', '🐸', '🐙', '🐵', '🦄', '🐞', '🦀', '🐟', '🐊', '🐓', '🦃', '🐿']);
    document.querySelector('#timer').innerHTML = game.formatTime(game.remaining);
    Array.from(document.querySelectorAll('.card')).forEach(function (elem, index) {
        elem.classList.remove('success', 'flip', 'fail');
        elem.addEventListener('click', flipCard);
    });
}

newGame();