using System;
using System.Collections.Generic;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Foods;

namespace StoryToPizzaStore {
    class Restaurant {
        public string name;
        public string address;
        public List<Food> menu = new List<Food>();
        // 这不太好, 一眼看不出元素是什么. 不过也没办法, 套餐类的基类是个接口
        public List<Combo> comboMenu = new List<Combo>(); 

        // 无参构造
        private Restaurant() {
            ;
        }

        // 有参构造
        public Restaurant(string name, string address) {
            this.name = name;
            this.address = address;
        }

        // 添加食物
        public Restaurant Add(Food food) {
            menu.Add(food);
            return this;
        }

        // 添加套餐
        public Restaurant AddCombo(Combo combo) {
            comboMenu.Add(combo);
            return this;
        }

        // 展示所有套餐
        public void ShowComboList() {
            int count = 1;
            foreach (Combo combo in comboMenu) {
                //System.Console.Write(
                //    "======== 套餐" + count + " ========\n" +
                //    "***** 名称: " + combo.name + " *****\n" +
                //    "***** 披萨: " + combo.pizza + " *****\n" +
                //    "***** 热狗: " + combo.hotDog + " *****\n" + 
                //    "***** 可乐: " + combo.cola + " *****\n\n"
                //    );
                System.Console.WriteLine("======== 套餐" + count + " ========");
                combo.showCombo();
                count++;
            }
        }

        // 展示菜单
        public void ShowList() {
            System.Console.WriteLine("======== 菜品清单 ========");
            foreach (Food food in menu) {
                food.Show();
            }
        }
    }
}
