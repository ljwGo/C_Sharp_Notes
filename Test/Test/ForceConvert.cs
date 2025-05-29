using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Test {
    public class ForceConvert {
        public class InnerClass02 : object {
            public void F() {
                Console.WriteLine("Execute in F");
            }

            public override string ToString() {
                return "Execute";
            }
        }

        public void Func(object o) {
            Console.WriteLine(o);
            Console.WriteLine((int)o);
        }

        public void Func02(object o) {
            ((InnerClass02)o).F();
        }

        // 测试object向值类型的强制转换
        public void Test() {
            Func(10);
        }

        // 测试object向引用类型的强制转换
        public void Test02() {
            Func02(new InnerClass02());
        }
    }
}
