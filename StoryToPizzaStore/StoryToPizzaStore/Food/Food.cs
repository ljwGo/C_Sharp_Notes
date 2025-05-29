using StoryToPizzaStore.Interfaces;
using System;

namespace StoryToPizzaStore {
    class Food : IFood {
        // 太久了, 都忘了abstract和virtual的区别
        public string name;
        public int quantity;
        public decimal price;
        virtual public void Show(){
            System.Console.WriteLine("名称: " + name);
            System.Console.WriteLine("数量: " + quantity);
            System.Console.WriteLine("价格: " + price);
            System.Console.WriteLine();
        }
    }
}
