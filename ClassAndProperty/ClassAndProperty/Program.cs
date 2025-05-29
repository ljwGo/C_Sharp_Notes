using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

// 特点的, C#的Json序列化类, 其类必须有[serializable]修饰
// 同时, 可以序列化的必须是类内的属性
namespace ClassAndProperty
{
    static class Program
    {
        class Property {
            // 属性的默认写法, 使用默认的构造器
            public string name
            {
                get; set;
            }
            // 特点:
            // 1.get和set后必须跟; 并且没有(),
            // 2.get有return返回
            // 3.set中使用value上下文关键字
            // 4.属性后的{}, 后面不加;号
        }

        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
