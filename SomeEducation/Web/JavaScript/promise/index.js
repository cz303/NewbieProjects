/**
 * @param {Function[]} operations
 * @param {Function} callback
 */
module.exports = function (operations, callback) {

    executing = [];

    operations.forEach(function (item) {
        executing.push(execute(item));
    });

    function execute(func) {
        return new Promise(function (resolve, reject) {
            func(next);

            function next() {
                if (arguments.length == 1) {
                    reject(arguments[0]);
                } else {
                    resolve(arguments[1]);
                }
            }
        });
    }

    Promise
        .all(executing)
        .then(function (data) {
            callback(null, data);
        }, function (error) {
            callback(error, null);
        });

};