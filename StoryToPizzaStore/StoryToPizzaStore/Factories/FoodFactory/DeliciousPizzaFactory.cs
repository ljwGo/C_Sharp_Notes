using StoryToPizzaStore.Common;
using StoryToPizzaStore.Interfaces;

namespace StoryToPizzaStore {
    class DeliciousPizzaFactory : Singleton<DeliciousPizzaFactory>, IFoodFactory {
        public Food GetFood() {
            return new Pizza("deliciousPizza", 20, new decimal(35), Level.Three);
        }
    }
}
