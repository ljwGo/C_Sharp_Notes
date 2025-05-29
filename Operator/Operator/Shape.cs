using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Operator
{
    class Shape
    {
    }

    class Square
    {
        public void Draw()
        {
            Console.WriteLine("++++++");
            for (int i = 0; i < 4; i++)
            {
                Console.WriteLine("+    +");
            }
            Console.WriteLine("++++++\n");
        }

        // 自定义操作符
        public static CombineShape operator +(Square s1, Square s2)
        {
            return new CombineShape(s1, s2);
        }
    }

    class CombineShape
    {
        List<Square> components = new List<Square>();

        public CombineShape() { }
        public CombineShape(Square s1, Square s2)
        {
            components.Add(s1);
            components.Add(s2);
        }

        public void Draw()
        {
            Console.WriteLine("-----组合图形-----");
            foreach (var p in components)
            {
                p.Draw();
            }
            Console.WriteLine("------------------");
        }
    }
}
