// var assert = require('assert');

var Market = require('./traders');

const _TRADERS = 60;
// const _INCOME_PERIOD = 365;
const _YEARS = 100;

var traders = [];

// Заполняем массив трейдеров
for (let i = 0; i < _TRADERS; i++) {
    switch (true) {
        case i < (_TRADERS / 6):
            traders.push(new Market.Altruist(i, 0));
            break;

        case i < (_TRADERS / 6) * 2:
            traders.push(new Market.Scum(i, 0));
            break;

        case i < (_TRADERS / 6) * 3:
            traders.push(new Market.Sharingan(i, 0))
            break;

        case i < (_TRADERS / 6) * 4:
            traders.push(new Market.Random(i, 0))
            break;

        case i < (_TRADERS / 6) * 5:
            traders.push(new Market.Fallen(i, 0))
            break;

        case i < (_TRADERS / 6) * 6:
            traders.push(new Market.Quirky(i, 0))
            break;
    }
}

// assert.equal(traders.length, _TRADERS);

// Функция эмуляции торговли между парами торговцев за год
function action() {

    // Очищаем историю сделок за год
    for (let index = 0; index < traders.length; index++) {
        traders[index].history = [];
    }

    // Перемешиваем случайным образом трейдеров
    // traders.sort(compareRandom);

	// Торгуем
    for (let index = 0; index < traders.length; index++) {
        for (let indx = index; indx < traders.length; indx++) {
            for (let i = 0; i < (Math.random() * (10 - 5) + 5); i++) {
                Market.Trade(traders[index], traders[indx])
            }
        }
    }

    // Сортируем по доходам
    traders.sort(compareIncome);

    var stats = {};
    for (let index = 0; index < traders.length; index++) {
        isNaN(stats[traders[index].type]) ? stats[traders[index].type] = 1 : stats[traders[index].type] += 1;
    }

    // Неудачные торговцы выходят в окно
    // На их место приходят новые    
    for (let index = traders.length * 0.8; index < traders.length; index++) {
            switch (traders[traders.length - index].constructor.name) {
                case 'Altruist':
                traders[index] = new Market.Altruist(traders[index].id, traders[index].adena);
                    break;
                case 'Scum':
                traders[index] = new Market.Scum(traders[index].id, traders[index].adena);
                    break;
                case 'Sharingan':
                traders[index] = new Market.Sharingan(traders[index].id, traders[index].adena);
                    break;
                case 'Random':
                traders[index] = new Market.Random(traders[index].id, traders[index].adena);
                    break;
                case 'Fallen':
                traders[index] = new Market.Fallen(traders[index].id, traders[index].adena);
                    break;
                case 'Quirky':
                traders[index] = new Market.Quirky(traders[index].id, traders[index].adena);
                    break;
            }
    }
    return stats;
}

compareRandom = function () {
    return Math.random() - 0.5;
}
compareId = function (a, b) {
    return a.id < b.id ? -1 : 1;
}
compareIncome = function (a, b) {
    return a.income > b.income ? -1 : 1;
}



var statistic = [];

// Royal battle
for (let index = 0; index < _YEARS; index++) {
    statistic.push({
        year: index+1,
        stats: action()
    });    
}


// traders.sort(compareId);
// traders.forEach(trader => {
//     console.log(`${trader.id} ${trader.type} $${trader.adena} \t ${trader.income} / ${trader.history.length}`);
// }); 

console.log(statistic[0]);
console.log(statistic[1]);
console.log(statistic[Math.round(_YEARS/10)]);
console.log(statistic[Math.round(_YEARS/5)]);
console.log(statistic[_YEARS-1]);