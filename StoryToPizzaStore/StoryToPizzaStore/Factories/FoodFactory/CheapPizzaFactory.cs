using StoryToPizzaStore.Common;
using StoryToPizzaStore.Interfaces;

namespace StoryToPizzaStore {
    class CheapPizzaFactory: Singleton<CheapPizzaFactory>, IFoodFactory {
        public Food GetFood() {
            return new Pizza("CheapPizza", 10, new decimal(15.5), Level.One);
        }
    }
}
