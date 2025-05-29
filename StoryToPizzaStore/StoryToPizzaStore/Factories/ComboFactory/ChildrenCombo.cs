using System;
using System.Collections.Generic;
using System.Text;
using StoryToPizzaStore.Interfaces;
using StoryToPizzaStore.Common;

namespace StoryToPizzaStore.Factories.ComboFactory {
    class ChildrenCombo : Singleton<ChildrenCombo>, ICombo {
        public string GetName() {
            return "儿童套餐";
        }

        public Food GetCola() {
            // 返回百事可乐
            return BaiShiCola.Instance.GetFood();
        }

        public Food GetPizza() {
            // 不严谨, 应该严格返回具体的派生类型, 比如Cola, Pizza和HotDog. 而不是Food
            return DeliciousPizzaFactory.Instance.GetFood();
        }

        public Food GetHotDog() {
            return null;
        }
    }
}
