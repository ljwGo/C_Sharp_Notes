using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;

namespace StoryToPizzaStore.Foods {
    class Combo {
        public string name;
        public Food pizza;
        public Food cola;
        public Food hotDog;

        private Combo() {
            ;
        }

        public Combo(ICombo comboFactory) {
            this.name = comboFactory.GetName();
            this.pizza = comboFactory.GetPizza();
            this.cola = comboFactory.GetCola();
            this.hotDog = comboFactory.GetHotDog();
        }

        public void showCombo() {
            System.Console.WriteLine("套餐名称: " + name );
            System.Console.WriteLine("披萨信息: ");
            if (pizza != null) {
                pizza.Show();
            }
            System.Console.WriteLine("可乐信息: ");
            if (cola != null) {
                cola.Show();
            }
            System.Console.WriteLine("热狗信息");
            if (hotDog != null) {
                hotDog.Show();
            }
        }
    }
}
