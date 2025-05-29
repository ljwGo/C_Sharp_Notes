using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Test {
    class ThreadWaitOneReturnValue {
        public static AutoResetEvent auto = new AutoResetEvent(false);

        public static void F() {
            Console.WriteLine(1);
            Console.WriteLine(auto.WaitOne());
            Console.WriteLine(2);
            //bool value = auto.WaitOne();
            //Console.WriteLine(value);
            auto.WaitOne();
            Console.WriteLine(3);
        }

        // 情况01: 使用Start方法时, 子线程直到遇到首个WaitOne才阻塞
        public static void Test() {
            Thread thread = new Thread(F);
            thread.Start();
            auto.Set();
        }

        // 情况02: 主线程直接执行3次auto.Set, 而子线程仅执行一次WaitOne
        // 明显的, Set控制的应该是一个bool值, 而非计数器
        /* 注: 这里无法使用console.writeline的方法给出提示信息, 因为它是io
         * 会减慢速度, 导致一次auto.Set后阻塞一段时间, 能够对上子线程地waitOne
        */
        public static void Test02() {
            Thread thread = new Thread(F);
            thread.Start();
            auto.Set();
            auto.Set();
            auto.Set();
        }

        // 情况03: 主线程使用Join方法加入子线程(子线程完成任务后, 才会回到主线程);
        // 实际情况是, 由于子线程阻塞了, 所以主线程也阻塞了(主线程并没有智能地返回)
        public static void Test03() {
            Thread thread = new Thread(F);
            thread.Start();
            auto.Set();
            Console.WriteLine("第一次开锁");
            thread.Join();
            auto.Set();
            Console.WriteLine("第二次开锁");
            thread.Join();
            auto.Set();
            Console.WriteLine("第三次开锁");
        }
    }
}
