using System;
using System.Threading;

namespace Test {
    internal class ThreadMultipleInvoke {

        class TestThreadTask {
            int counter = 0;

            public void Run() {
                Console.WriteLine(counter++);
            }
        }

        // 测试：重复Start一个执行过的线程
        // 结果：报错
        public void Test() {
            TestThreadTask task = new TestThreadTask();

            Thread th01 = new Thread(task.Run);
            th01.Start();
            th01.Join();
            //th01.Start();
        }
    }
}
