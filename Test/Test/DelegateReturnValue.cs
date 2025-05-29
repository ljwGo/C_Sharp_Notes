using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    public delegate int SimpleDelegate(int n);
    public delegate Complex ComplexDelegate();

    public class Complex {
        public float realPart;
        public float imaginary;

        public Complex(float realPart, float imaginary) {
            this.realPart = realPart;
            this.imaginary = imaginary;
        }

        // 这部分代码与其他测试冲突, 请在必要时注销
        // += 无法被重载
        public static Complex operator +(Complex complex, Complex otherComplex) {
            return new Complex(complex.realPart + otherComplex.realPart, complex.imaginary + otherComplex.imaginary);
        }

        public override string ToString() {
            return realPart.ToString() + " " + imaginary.ToString() + "i";
        }
    }

    class DelegateReturnValue {
        public SimpleDelegate simpleDelegate;
        public ComplexDelegate complexDelegate;

        public DelegateReturnValue() {
            simpleDelegate += Func01;
            simpleDelegate += Func02;
            simpleDelegate += Func03;
            complexDelegate += ComplexFunc;
            complexDelegate += ComplexFunc02;
            complexDelegate += ComplexFunc03;
        }

        public int Func01(int n) {
            Console.WriteLine("Execute in Func01");
            return n;
        }

        public int Func02(int n) {
            Console.WriteLine("Execute in Func02");
            return n*2;
        }

        public int Func03(int n) {
            Console.WriteLine("Execute in Func03");
            return n * 3;
        }

        // 测试一个委托是否可以执行多个方法
        // 结果: 可以
        public void Test() {
            simpleDelegate(10);
        }

        // 测试多个方法的委托的返回值
        // 结果: 返回最后一个方法的结果
        public void Test02() {
            Console.WriteLine(simpleDelegate(10));
        }

        public Complex ComplexFunc() {
            return new Complex(1, 1);
        }

        public Complex ComplexFunc02() {
            return new Complex(2, 2);
        }

        public Complex ComplexFunc03() {
            return new Complex(3, 3);
        }

        // 测试复杂返回值的多个方法的委托的返回值
        // 结果: 返回的是最后一个方法的返回值
        public void Test03() {
            Console.WriteLine(complexDelegate());
        }

        // 测试重写 + 运算符后的结果
        // 结果: 没有效果, complex并没有相加
        public void Test04() {
            Test03();
        }

        
    }
}
