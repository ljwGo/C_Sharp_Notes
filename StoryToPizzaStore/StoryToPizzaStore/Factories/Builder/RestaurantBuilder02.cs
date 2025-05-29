using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Foods;
using StoryToPizzaStore.Factories.ComboFactory;

namespace StoryToPizzaStore.Factories.FoodFactory {
    class RestaurantBuilder02 {
        public Restaurant GetBigRestaurant() {
            return new Restaurant("kakolo", "上海")
                .Add(BaiShiCola.Instance.GetFood())
                .Add(CheapPizzaFactory.Instance.GetFood())
                .Add(CommonPizzaFactory.Instance.GetFood())
                .Add(KeCouCola.Instance.GetFood())
                .Add(DeliciousPizzaFactory.Instance.GetFood())
                // 添加套餐
                .AddCombo(new Combo(ChildrenCombo.Instance))
                .AddCombo(new Combo(LuxuryCombo.Instance))
                .AddCombo(new Combo(StandardCombo.Instance));
        }
        public Restaurant GetSmallRestaurant() {
            return new Restaurant("kakolo", "阳山")
                .Add(CheapPizzaFactory.Instance.GetFood())
                .Add(CommonPizzaFactory.Instance.GetFood())
                .Add(KeCouCola.Instance.GetFood())
                .AddCombo(new Combo(ChildrenCombo.Instance))
                .AddCombo(new Combo(StandardCombo.Instance));
        }
        // ...这里可以新增
    }
}
