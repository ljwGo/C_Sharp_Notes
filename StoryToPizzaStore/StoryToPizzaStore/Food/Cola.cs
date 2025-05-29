using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore {
    class Cola : Food {
        private Cola() {; }
        public Cola(string name, int quantity, decimal price){
            this.name = name;
            this.quantity = quantity;
            this.price = price;
        }
    }
}
