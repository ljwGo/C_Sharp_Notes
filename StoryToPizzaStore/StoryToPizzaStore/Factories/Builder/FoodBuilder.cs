using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore.Factories.FoodFactory {
    class FoodBuilder {
        /*
            这里都返回Food类型似乎不太好, 我想改为具体的HotDog, Pizza和Cola派生类型, 但是GetFood方法被接口限制, 返回值类型必须为Food, 多态支持派生类对象赋值给基类变量, 反之不行. 不写具体的, 从Builder这里容易混淆得到的类型具体是Food的什么派生类. 不过能通过Food类型使用派生类的所有方法, 似乎问题不大.
         */
        public Food GetHotHotDog() {
            return HotHotDog.Instance.GetFood();
        }
        public Food GetKeCouCola() {
            return KeCouCola.Instance.GetFood();
        }
        public Food GetBaiShiCola() {
            return BaiShiCola.Instance.GetFood();
        }
        public Food GetCommonPizza() {
            return CommonPizzaFactory.Instance.GetFood();
        }
        public Food GetCheapPizza() {
            return CheapPizzaFactory.Instance.GetFood();
        }
        public Food GetDeliciousPizza() {
            return DeliciousPizzaFactory.Instance.GetFood();
        }
        // 这里之后再添加...
    }
}
