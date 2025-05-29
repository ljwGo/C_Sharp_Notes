using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories {
    class LuxuryCombo : Singleton<LuxuryCombo>, ICombo {
        public string GetName() {
            return "豪华套餐";
        }

        public Food GetPizza() {
            return DeliciousPizzaFactory.Instance.GetFood();
        }

        public Food GetHotDog() {
            return HotHotDog.Instance.GetFood();
        }

        public Food GetCola() {
            return BaiShiCola.Instance.GetFood();
        }
    }
}
