using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories {
    class KeCouCola : Singleton<KeCouCola>, IFoodFactory {
        public Food GetFood() {
            return new Cola("可口可乐", 10, 3);
        }
    }
}
