using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories {
    class BaiShiCola : Singleton<BaiShiCola>, IFoodFactory {
        public Food GetFood() {
            return new Cola("百事可乐", 20, 3);
        }
    }
}
