using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore.Interfaces {
    interface ICombo {
        Food GetCola();
        Food GetHotDog();
        Food GetPizza();
        string GetName();
    }
}
