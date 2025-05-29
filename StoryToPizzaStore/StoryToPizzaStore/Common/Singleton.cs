using System;
using System.Collections.Generic;
using System.Text;

namespace StoryToPizzaStore.Common{
    class Singleton<T> where T : class, new() {
        static private T instance = null;
        static public T Instance { 
            get { 
                if (instance == null) {
                    instance = new T();
                }
                return instance; 
            } 
        }
    }
}
