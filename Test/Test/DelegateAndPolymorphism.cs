using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    public class DelegateAndPolymorphism {
        public Func<object> delegate01;
        public Func<int> delegate02;

        public object Func() {
            return null;
        }

        public int Func02() {
            return 10;
        }

        // 委托并没有返回值重载一说
        public void Test() {
            delegate01 += Func;
            //delegate02 += Func;
            //delegate01 += Func02;
            delegate02 += Func02;
        }
    }
}
