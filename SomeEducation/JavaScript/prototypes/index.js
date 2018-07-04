module.exports = Collection;

/**
 * Конструктор коллекции
 * @constructor
 */
function Collection() {
    this.array = [];
}

/** 
 * Методы коллекции 
 */
Collection.prototype.values = function () {
    // Возвращаем массив 
    return this.array;
};

Collection.prototype.append = function (element) {
    // Добавляем элемент
    if (!(element instanceof Collection))
        this.array.push(element);
    else
        appendArray(this, element.values());
};

Collection.prototype.at = function (id) {
    // Выводим элемент
    if (this.array[id - 1] != undefined)
        return this.array[id - 1];
    else
        return null;
};

Collection.prototype.removeAt = function (id) {
    // Удаляем элемент
    if (this.array[id - 1] != undefined) {
        this.array.splice(id - 1, 1);
        return true;
    } else
        return false;
};

Collection.prototype.count = function () {
    // Выводим количество элементов
    return this.array.length;
};

function appendArray(collection, array) {
    array.forEach(function (element) {
        collection.append(element);
    });
}

/**
 * Создание коллекции из массива значений
 */
Collection.from = function () {

    if (!(arguments[0] instanceof Collection)) {
        var items = new Collection();

        appendArray(items, arguments[0]);

        return items;
    }
};