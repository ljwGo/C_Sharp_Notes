using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using System.Reflection;

namespace Variable
{
    class Program
    {
        static void Main(string[] args)
        {
            // Form form = new Form();
            // form.Text = "Hello, world";
            // form.ShowDialog();

            // 变量知道自己的父类（基类）和自己拥有的属性和方法
            //Type myType = typeof(Form);
            //Console.WriteLine(myType.BaseType.FullName);
            //PropertyInfo[] plnfo = myType.GetProperties();
            //MethodInfo[] mInfo = myType.GetMethods();
            //foreach (var p in plnfo)
            //{
            //    Console.WriteLine(p.Name);
            //}
            //foreach (var k in mInfo)
            //{
            //    Console.WriteLine(k.Name);
            //}

            // C#是强类型语言
            //int a = 100;
            //long b = 100L;
            //double c = 4.022;
            //float d = 50.5F;


            //public int CalcSum(int x)
            //{
            //    if (x == 1) 
            //    { 
            //        return 1;
            //    }
            //    else
            //    {
            //        return x + CalcSum(x - 1);
            //    }
            //}

            // 栈溢出
            //Method.BadMethod();
            //unsafe
            //{
            //    int *p = stackalloc int[9999999];
            //}
        }
    }

    //class Method
    //{
    //    public static void BadMethod()
    //    {
    //        int a = 100;
    //        BadMethod();
    //    }
    //}
}
