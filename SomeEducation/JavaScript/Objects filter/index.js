/**
 * @param {Array} collection
 * @params {Function[]} – Функции для запроса
 * @returns {Array}
 */

function query(collection) {
    var result = JSON.parse(JSON.stringify(collection));
    var filter = {};
    var selected = [];

    if (arguments.length == 1) {
        return result;
    } else {
        for (var i = 1; i < arguments.length; i++) {
            if (arguments[i].name == 'select') {
                selected = arguments[i](selected);
            }
            if (arguments[i].name == 'filterIn') {
                arguments[i](filter);
            }
        }

        // Сначала фильтруем 
        // Для каждого ключа в фильтре
        Object.keys(filter).forEach(function(filter_key) {
            // Перебираем возвращаемый массив
            result = result.filter(function(human) {
                // Если ключ есть у элемента
                // И элемент содержит значение из фильтра
                return human.hasOwnProperty(filter_key) &&
                    (filter[filter_key].indexOf(human[filter_key]) !== -1);
            });
        });

        // Выборка полей в отфильтрованном массиве
        selected.forEach(function (prop) {
            result.forEach(function(item) {
                if(item.hasOwnProperty(prop)) {
                Object.keys(item).forEach(function(key) {
                    if (selected.indexOf(key) == -1)
                    // Удаляем поле у объекта
                        delete item[key];
                });
            }
            });
        });
    }
    return result;
}

/**
 * @param {String} property – Свойство для фильтрации
 * @param {Array} values – Массив разрешённых значений
 */

function filterIn(property, values) {
    var obj = {};
    var newValues = Array.isArray(values) ? values : [].concat(values);

    // Оставляем в фильтре только строки или числа
    newValues = newValues.filter(function(value) {
        return typeof(value) == 'string' || typeof(value) == 'number';
    });

    // Функция для возвращения фильтра с перекрытием новых параметров
    return function filterIn(filter) {
        if (!filter.hasOwnProperty(property)) {
            filter[property] = newValues;
        } else {
            filter[property] = [].slice.call(newValues).filter(
                function(value) { return filter[property].indexOf(value) !== -1; }
            );
            // Если условие фильтра станет пустым, удалить фильтр
             if (filter[property].length == 0) delete filter[property];
        }
        return filter;
    }
}

/**
 * @params {String[]}
 */
function select() {
    var newValues = [].slice.call(arguments);
    return function select(params) {
        params = newValues.filter(
            function(value) {
                return params.length == 0 || params.indexOf(value) !== -1;
            });
        return params;
    }
}


module.exports = {
    query: query,
    select: select,
    filterIn: filterIn
};