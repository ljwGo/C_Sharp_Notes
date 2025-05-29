using StoryToPizzaStore.Common;
using StoryToPizzaStore.Interfaces;

namespace StoryToPizzaStore {
    class CommonPizzaFactory: Singleton<CommonPizzaFactory>, IFoodFactory {
        public Food GetFood() {
            return new Pizza("commonPizza", 10, new decimal(20), Level.Two);
        }
    }
}
