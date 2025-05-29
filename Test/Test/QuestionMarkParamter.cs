using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    // int? 似乎是Nullable<int>的语法糖
    class QuestionMarkParamter {
        public static void Func(int o) {
            ;
        }

        public static void Func02(int? o) {
            ;
        }

        // 测试一般引用类型参数, 传入null
        // 结果: 引用类型可以传入null
        public static void Test() {
            //Func(null);
        }

        // 测试引用类型不传入参数
        // 结果: 符合形参实参一一对应, 无论是否加?, 都要传入
        public static void Test02() {
            //Func02();
            //Func();
        }

        // 测试Nullable<T>和T; 形参? 和 形参之间的区别
        // 结果: Nullable使值类型可以赋予null
        //       而值类型? 可以传入null类型
        //       而引用类型? 还能传入为赋值变量
        public static void Test03() {
            int? n;
            //int m;

            n = null;
            //m = null;

            //Func(n);
            //Func(m);
            Func02(n);
            //Func02(m);
        }
    }
}
