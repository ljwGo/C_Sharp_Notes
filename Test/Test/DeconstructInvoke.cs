using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    public class DeconstructInvoke {
        public class InnerClass{
            public string name;
            public int age;

            public InnerClass() {
                name = "内置类的名称";
                age = 18;
            }

            public void Deconstruct(out string name, out int age) {
                name = this.name;
                age = this.age;
            }
        }

        // 测试给类进行解构赋值
        // 结果: 可以
        public void Test() {
            (string s, int age) = new InnerClass();
            Console.WriteLine("s: " + s);
            Console.WriteLine("age: " + age);
        }

        // 测试列表是否可以进行解构赋值
        // 结果: 不可以, List缺少Deconstruct定义
        public void Test02() {
            //(string s, int age) = new List<int> { };
            //Console.WriteLine("s: " + s);
            //Console.WriteLine("age: " + age);
        }

        // 测试是否可以解构调用
        // 结果: 不可以
        public void Test03() {
            //FuncForTest03(new InnerClass());
        }

        public void FuncForTest03(string name, int age) {
            Console.WriteLine(name);
            Console.WriteLine(age);
        }
    }
}
