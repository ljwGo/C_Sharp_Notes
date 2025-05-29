using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.Reflection;

namespace Operator
{
    class Program
    {
        const String path = "D:\\DontStarveModCreate\\Software\\1.4.1\\SquishNET.dll";

        // 操作符也叫运算符，具体种类参考帮助文档
        static void Main(string[] args)
        {
            //操作符本质是函数的简记法
            //使用operator关键字自定义操作符
            //类Shape下由自定义操作符
            Square s1 = new Square();
            Square s2 = new Square();
            CombineShape c = s1 + s2;
            s1.Draw();
            s2.Draw();
            c.Draw();

            ReflectAssembly();
        }

        static void ReflectAssembly() {
            try {
                Assembly assembly = Assembly.LoadFrom(path);
                var pubTypesQuery = from type in assembly.GetTypes()
                                    where type.IsPublic
                                    from method in type.GetMethods()
                                    where method.ReturnType.IsArray == true
                                        || (method.ReturnType.GetInterface(
                                            typeof(System.Collections.Generic.IEnumerable<>).FullName!) != null
                                        && method.ReturnType.FullName != "System.String")
                                    group method.ToString() by type.ToString();

                foreach (var groupOfMethods in pubTypesQuery) {
                    Console.WriteLine("Type: {0}", groupOfMethods.Key);
                    foreach (var method in groupOfMethods) {
                        Console.WriteLine("  {0}", method);
                    }
                }
            }
            catch (Exception e) {
                Console.WriteLine(e.ToString());
            }
        }
    }
}
