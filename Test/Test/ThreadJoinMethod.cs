using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Test {
    class ThreadJoinMethod {
        static void Print(object message) {
            for (int i=0; i<1000; i++) {
                message = message as string;
                Console.WriteLine(message);
            }
        }

        // 测试Join是优先执行某个线程; 还是说执行完子线程前, 当前线程阻塞不结束
        // 结果, 是后者
        public static void Test() {
            Thread thread01 = new Thread(new ParameterizedThreadStart(Print));
            Thread thread02 = new Thread(new ParameterizedThreadStart(Print));
            thread01.Start("haha");
            thread02.Start("aaaa");
            thread01.Join();
            thread01.Join();
            Console.WriteLine("主线程结束");
        }
    }
}
