using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore.Factories {
    class RestaurantBuilder {
        public Restaurant GetBigRestaurant() {
            // 之前是要什么餐厅对象, 就访问什么餐厅工厂, 现在则统一从建造者对象中获取
            return BigRestaurantFactory.Instance.GetRestaurant();
        }
        public Restaurant GetSmallRestaurant() {
            return SmallRestaurantFactory.Instance.GetRestaurant();
        }
        // ... 这里还可以添加
    }
}
