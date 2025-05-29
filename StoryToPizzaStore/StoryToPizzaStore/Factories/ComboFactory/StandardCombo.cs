using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories.ComboFactory {
    class StandardCombo : Singleton<StandardCombo>, ICombo{
        public string GetName() {
            return "标准套餐";
        }

        public Food GetCola() {
            return KeCouCola.Instance.GetFood();
        }

        public Food GetPizza() {
            return CommonPizzaFactory.Instance.GetFood();
        }

        public Food GetHotDog() {
            return HotHotDog.Instance.GetFood();
        }
    }
}
