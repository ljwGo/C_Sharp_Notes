using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

/*
    从测试结果看, 可以看出;
    即使是线程公用的变量, (不是读文件这种延迟很大的操作, 而是修改一个很简单的int类型, 虽然也算io)
    也会发生线程带来的数据安全问题
    不存在数据锁
    并且, 线程执行命令的最小单位依旧是指令, 而非语句
 */
namespace Test {
    public class ThreadSecurity {
        public static int number = 0;
        public static List<int> li01 = new List<int>{ 0 };
        public static List<int> li02 = new List<int>();
        public static int quantity = 1000;

        public static void AutomaticDecrease() {
            for (int i = 0; i < quantity; i++) {
                number--;
            }
        }

        public static void AutomaticDecreaseQuote() {
            for (int i = 0; i < quantity; i++) {
                li01[0]--;
            }
        }

        public static void AutomaticIncrease() {
            for (int i = 0; i < quantity; i++) {
                number++;
            }
        }

        public static void AutomaticIncreaseQuote() {
            for(int i=0; i < quantity; i++) {
                li01[0]++;
            }
        }

        public static void AutomaticIncreaseNumber() {
            for (int i = 0; i < quantity; i++) {
                // next statement will throw out of index range error!!
                //if (li02[li02.Count - 1] > quantity * 2){
                //    Console.WriteLine(true);
                //};
                li02.Add(i);
            }
        }

        public static void AutomaticDecreaseNumber() {
            for (int i = 0; i < quantity; i++) {
                li02.RemoveAt(li02.Count-1);
            }
        }

        // 测试不同线程修改值类型时, 是否发生数据错乱.
        // 结果: 会发生
        public static void Test() {
            Thread thread01 = new Thread(AutomaticDecrease);
            Thread thread02 = new Thread(AutomaticIncrease);
            thread01.Start();
            thread02.Start();
            thread01.Join();
            thread02.Join();

            Console.WriteLine(number);
        }

        // 测试不同线程修改引用类型时, 是否发生数据错乱.
        // 结果: 会发生
        public static void Test02() {
            Thread thread01 = new Thread(AutomaticDecreaseQuote);
            Thread thread02 = new Thread(AutomaticIncreaseQuote);
            thread01.Start();
            thread02.Start();
            thread01.Join();
            thread02.Join();

            Console.WriteLine(li01[0]);
        }

        // 测试不同线程对容器类型执行增删操作是否会出现问题
        // 结果: 会发生(这个具体原因不好想)
        public static void Test03() {
            for (int i=0; i < quantity; i++) {
                li02.Add(i);
            }
            Thread thread01 = new Thread(AutomaticDecreaseNumber);
            Thread thread02 = new Thread(AutomaticIncreaseNumber);

            //thread01.Start();
            thread02.Start();
            thread01.Join();
            thread02.Join();

            Console.WriteLine(li02.Count);
        }
    }
}
