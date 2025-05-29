#define BUG
using System;
using System.Diagnostics;

namespace Attribute {
    [AttributeUsage(AttributeTargets.Class // 规定可以该特性可以跟在Class前
        | AttributeTargets.Method // 规定可以该特性可以跟在Method前
        | AttributeTargets.Field
        // 规定可以该特性可以跟在Field前
        | AttributeTargets.Property
        // 规定可以该特性可以跟在Property前
        , AllowMultiple = true)]
    // 允许该特性被重复使用统一类或其它前
    class BugInfoAttr : System.Attribute { // 自定义特性类必须继承Attribute

        public BugInfoAttr(string devloptor, string bugName, string fixTime) {
            this.Devloptor = devloptor;
            this.BugName = bugName;
            this.FixTime = fixTime;
        }

        public string Devloptor
        {
            get;
            set;
        }
        public string BugName
        {
            get;
            set;
        }
        // DateTime不是特性值的有效类型, DateTime不能作为自定义特性类的成员属性
        public string FixTime
        {
            get;
            set;
        }
        public void ShowInfo() {
            Console.WriteLine("开发者: " + Devloptor);
            Console.WriteLine("BUG名称: " + BugName);
            Console.WriteLine("修复时间: " + FixTime);
        }
    }

    [BugInfoAttr("ljw", "textBug", "2022-7-20")]
    class MyClass {
        public void ShowAttr() {
            Type type = typeof(MyClass);
            foreach (object obj in type.GetCustomAttributes(false)) {
                BugInfoAttr bugInfoAttr = (BugInfoAttr)obj;
                bugInfoAttr.ShowInfo();
            }
        }
    }

    class MyClass02 {
        [BugInfoAttr("ljw", "text", "2222-2-2")]
        public void Text01()
        {
            Console.WriteLine("测试01");
        }

        [BugInfoAttr("ljw", "test", "2000-2-1")]
        public void Text02()
        {
            Console.WriteLine("测试02");
        }

        [BugInfoAttr("jj", "fix", "1920-11-23")]
        public void Text03(string attr) {
            Console.WriteLine("测试03, 该方法有参数, 为: " + attr);
        }
    }

    class BugClass{
        [Conditional("BUG")]
        public static void BugFunc() {
            Console.WriteLine("BugFunc in BugClass");
        }

        [Conditional("RELEASE")]
        public static void ReleaseFunc() {
            Console.WriteLine("ReleaseFunc in BugClass");
        }
    }

    class Program {
        static void Main(string[] args) {
            //BugClass.BugFunc();
            //BugClass.ReleaseFunc();

            //MyClass myClass = new MyClass();
            //myClass.ShowAttr();

            MyClass02 myClass02 = new MyClass02();
            Type type = myClass02.GetType();

            foreach (System.Reflection.MethodInfo method in type.GetMethods()) {
                //method.Invoke(myClass02);
                foreach (System.Attribute attr in method.GetCustomAttributes(false)) {
                    // 下面的强制转换会发生错误, 原因是, 获取的方法中, 有继承自Object的Equal等方法, 该方法没有BugInfoAttr特性, 强制转换时会出现错误
                    //BugInfoAttr bugInfo = (BugInfoAttr)attr;
                    BugInfoAttr bugInfo = attr as BugInfoAttr;
                    if (bugInfo != null) {
                        bugInfo.ShowInfo();
                    }
                }
            }
        }
    }
}
