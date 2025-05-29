using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test02 {
    class Override {
        // 测试重写方法调用基类的同名方法
        // 结果: 可以, 重写可以实现方法逻辑的扩充!!!
        public void Test() {
            A a = new C();
            a.Func();
        }
    }

    class A {
        public virtual void Func() {
            Console.WriteLine("Func in A");
        }
    }

    class B : A{
        public override void Func() {
            Console.WriteLine("Func in B");
            base.Func();
        }
    }

    class C : B{
        public override void Func() {
            Console.WriteLine("Func in C");
            base.Func();
        }
    }
}
