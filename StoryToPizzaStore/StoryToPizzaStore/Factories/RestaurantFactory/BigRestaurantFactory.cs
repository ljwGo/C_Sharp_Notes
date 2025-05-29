using StoryToPizzaStore.Factories;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;
using StoryToPizzaStore.Foods;
using StoryToPizzaStore.Factories.ComboFactory;

namespace StoryToPizzaStore {
    class BigRestaurantFactory : Singleton<BigRestaurantFactory>, IRestaurantFactory{
        public Restaurant GetRestaurant() {
            return new Restaurant("kakolo", "上海")
                .Add(BaiShiCola.Instance.GetFood())
                .Add(CheapPizzaFactory.Instance.GetFood())
                .Add(CommonPizzaFactory.Instance.GetFood())
                .Add(KeCouCola.Instance.GetFood())
                .Add(DeliciousPizzaFactory.Instance.GetFood())
                .AddCombo(new Combo(ChildrenCombo.Instance))
                .AddCombo(new Combo(LuxuryCombo.Instance))
                .AddCombo(new Combo(StandardCombo.Instance)); 
        }
    }
}