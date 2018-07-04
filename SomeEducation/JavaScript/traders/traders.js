class Traders {
  constructor(id, kind, type, startWealth) {
    this.id = id;
    this.adena = startWealth; // золото
    this.history = []; // история сделок
    this.kind = kind; // честность
    this.type = type; // тип торговца
  }

  get income() {
    var profit = 0;
    this.history.forEach(trade => {
      profit += trade.earning
    });
    return profit;
  }

  update() {
    // do nothing
    return true;
  }

  deal() {
    var rnd = Math.random();
    var rt = rnd >= 0.05 ? this.kind : !this.kind;

    return rt;
  }

  trade(earning, traderID) {
    this.history.push({
      balance: this.adena,
      earning: earning,
      opponent: traderID
    })
    this.adena += earning;
  }

}

// Сделка между двумя торговцами
function Trade(trader1, trader2) {
  firstDeal = trader1.deal();
  secondDeal = trader2.deal();
  var income1, income2;
 
   if (firstDeal && secondDeal){
    income1 = 4; income2 = 4;
   }
   if(firstDeal == false && secondDeal == true){
    income1 = 5; income2 = 1;
   }
   if(firstDeal == true && secondDeal == false){
    income1 = 1; income2 = 5;
   }
   if(firstDeal == false && secondDeal == false){
    income1 = 2; income2 = 2;
   }

   trader1.trade(income1, trader2.id);
   trader2.trade(income2, trader1.id);
   trader1.update(secondDeal);
   trader2.update(firstDeal);
}
   

/* 
Альтруист 
*/
class Altruist extends Traders {
  constructor(id, startWealth) {
    super(id, true, 'altruist', startWealth);
  }
}

/* 
Кидала
*/
class Scum extends Traders {
  constructor(id, startWealth) {
    super(id, false, 'scum', startWealth);
  }
}

/* 
Хитрец
*/
class Sharingan extends Traders {
  constructor(id, startWealth) {
    super(id, true, 'sharingan', startWealth);
  }

  update(opponentBehavior) {
    this.kind = opponentBehavior;
  }
}

/* 
Непредсказуемый
*/
class Random extends Traders {
  constructor(id, startWealth) {
    super(id, true, 'random', startWealth);
    this.kind = (Math.random() - 0.5 > 0);
  }

  deal() {
    var rt  = this.kind;
    this.kind = (Math.random() - 0.5 > 0);
    return rt;
  }
}

/* 
Злопамятный
*/
class Fallen extends Traders {
  constructor(id, startWealth) {
    super(id, true, 'fallen', startWealth);
  }

  update(opponentBehavior) {
    if (opponentBehavior == false)
      this.kind = false;
  }
}

/* 
Ушлый
*/
class Quirky extends Traders {
  constructor(id, startWealth) {
    super(id, true, 'quirky', startWealth);
    this.patience = true;
  }

  update(opponentBehavior) {
    if (this.history.length < 4 && opponentBehavior == false)
      this.patience = false;
    if (this.history.length >= 4) {
      if (this.patience == false) {
        this.newType = 'scum';
        this.kind = false;
      } else {
        this.newType = 'sharingan';
        this.kind = opponentBehavior;
      }
    }
  }
}

module.exports = {
  Altruist: Altruist,
  Scum: Scum,
  Sharingan: Sharingan,
  Random: Random,
  Fallen: Fallen,
  Quirky: Quirky,
  Trade: Trade,
};