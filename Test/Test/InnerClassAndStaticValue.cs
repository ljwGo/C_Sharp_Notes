using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    class InnerClassAndStaticValue {
        class InnerClass {
            public static int n = 0;
        }

        public void innerStaticValueAdd() {
            Console.WriteLine(InnerClass.n++);
        }

        // 测试内部类中静态变量的特性
        // 结果: 和一般静态变量相同, 不同实例共用同一个静态变量
        public static void Test() {
            InnerClassAndStaticValue innerClass01 = new InnerClassAndStaticValue();
            InnerClassAndStaticValue innerClass02 = new InnerClassAndStaticValue();

            innerClass01.innerStaticValueAdd();
            innerClass02.innerStaticValueAdd();
        }
    }
}
