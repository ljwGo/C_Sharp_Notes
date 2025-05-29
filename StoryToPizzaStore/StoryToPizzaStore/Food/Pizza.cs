using System;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore {
    class Pizza: Food{
        readonly Level level;

        private Pizza() {
            ;
        }
        public Pizza(string name, int quantity, decimal price, Level level) {
            this.name = name;
            this.quantity = quantity;
            this.price = price;
            this.level = level;
        }
        override public void Show() {
            System.Console.WriteLine("名称: " + name);
            System.Console.WriteLine("数量: " + quantity);
            System.Console.WriteLine("价格: " + price);
            System.Console.WriteLine("等级: " + level);
            System.Console.WriteLine();
        }
    }
}