using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore {
    class HotDog : Food{
        private HotDog() {; }
        public HotDog(string name, int quantity, decimal price) {
            this.name = name;
            this.quantity = quantity;
            this.price = price;
        }
    }
}
