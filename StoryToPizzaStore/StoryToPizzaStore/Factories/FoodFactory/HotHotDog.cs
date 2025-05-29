using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories {
    class HotHotDog : Singleton<HotHotDog>, IFoodFactory {
        public Food GetFood() {
            return new HotDog("热的热狗", 12, 5);
        }
    }
}
