module.exports = {
    subscriptions: [],

    /**
     * @param {String} event
     * @param {Object} subscriber
     * @param {Function} handler
     */
    on: function(event, subscriber, handler) {

        if (!subscriber.hasOwnProperty(event)) {
            subscriber[event] = [handler];

            if (this.subscriptions.indexOf(subscriber) === -1) {
                this.subscriptions.push(subscriber);
            }
        } else {
            subscriber[event].push(handler);
        }
        return this;
    },

    /**
     * @param {String} event
     * @param {Object} subscriber
     */
    off: function(event, subscriber) {
        if (subscriber.hasOwnProperty(event)) {
            delete subscriber[event];
        }
        return this;
    },

    /**
     * @param {String} event
     */
    emit: function(event) {
        this.subscriptions.forEach(function(sub) {
            if (sub.hasOwnProperty(event)) {
                sub[event].forEach(function (func) {
                    func.call(sub);
                });
            }
        });
        return this;
    }
};