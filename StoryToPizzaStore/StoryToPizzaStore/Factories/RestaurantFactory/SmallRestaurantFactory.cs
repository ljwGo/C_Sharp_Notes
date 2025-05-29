using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Common;
using StoryToPizzaStore.Factories.ComboFactory;
using StoryToPizzaStore.Foods;
using StoryToPizzaStore.Interfaces;

namespace StoryToPizzaStore.Factories {
    class SmallRestaurantFactory : Singleton<SmallRestaurantFactory>, IRestaurantFactory {
            public Restaurant GetRestaurant() {
            return new Restaurant("kakolo", "阳山")
                .Add(CheapPizzaFactory.Instance.GetFood())
                .Add(CommonPizzaFactory.Instance.GetFood())
                .Add(KeCouCola.Instance.GetFood())
                .AddCombo(new Combo(ChildrenCombo.Instance))
                .AddCombo(new Combo(StandardCombo.Instance));
        }
    }
}
