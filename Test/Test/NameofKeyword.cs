using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    class NameofKeyword {
        public void Func(int x) {
            Console.WriteLine(x);
        }

        public void Func(float x) {
            Console.WriteLine(x);
        }

        // 测试nameof获取的类型的名称
        // 结果: 就是类名
        public void Test01() {
            Console.WriteLine(nameof(NameofKeyword));
        }

        // 测试nameof获取的对象的名称
        // 结果: 对象不能有名称
        //public void Test02() {
        //    Console.WriteLine(nameof(new NameofKeywordcs()));
        //}

        // 测试nameof获取方法组的名称
        // 结果: 就是方法名
        public void Test03() {
            Console.WriteLine($"方法组01名称 = {nameof(NameofKeyword.Func)}");
        }

        // 测试类型Type的名称
        // 结果: Type也没有名称
        //public void Test04() {
        //    Console.WriteLine(nameof(typeof(NameofKeyword)));
        //}
    }
}
