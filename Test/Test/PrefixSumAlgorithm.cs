using System;
using System.Threading;

namespace Test {
    internal class PrefixSumAlgorithm {

        const int threadCount = 16;
        const int gridSize = 256;

        static int prefixUnitSum = 2;
        static Random random = new Random(1);

        class ThreadTask {

            public static int[] grid = new int[gridSize];
            public static int unitSize = 1;

            int threadId;

            public ThreadTask(int threadId) {
                this.threadId = threadId;
            }

            public void ExecuteOne() {
                int gridId = threadId;

                while (gridId < gridSize) {
                    int unitId = (gridId / unitSize);
                    int oddOrEvenFlag = unitId % 2;

                    if (oddOrEvenFlag == 1) {
                        int previousUnitLastValue = grid[unitId * unitSize - 1];
                        grid[gridId] += previousUnitLastValue;
                    }

                    gridId += threadCount;
                }
            }
        }

        public void Test() {
            InitCounter();
            ShowGrid(16);
            CalcSum();
            Console.WriteLine();
            Execute();
        }

        void InitCounter() {
            for (int i = 0; i < gridSize; i++) {
                ThreadTask.grid[i] = random.Next(4);
            }
        }

        void CalcSum() {
            int sum = 0;
            for (int i = 0; i <gridSize; i++) {
                sum += ThreadTask.grid[i];
            }
            Console.WriteLine("sum: " + sum);
        }

        void ShowGrid(int cols) {
            int rows = (int)Math.Floor((float)gridSize / cols);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int ix = i * rows + j;
                    if (ix < gridSize) {
                        Console.Write(ThreadTask.grid[ix] + " ");
                    }
                }
                Console.WriteLine();
            }
        }

        void Execute() {
            bool isFirst = true;

            ThreadTask[] threadTasks = new ThreadTask[threadCount];
            Thread[] threads = new Thread[threadCount];

            do {
                prefixUnitSum *= 2;
                ThreadTask.unitSize *= 2;

                if (isFirst) {
                    prefixUnitSum = 2;
                    ThreadTask.unitSize = 1;
                    isFirst = false;
                }

                for (int i = 0; i < threadCount; ++i) {
                    threadTasks[i] = new ThreadTask(i);
                    threads[i] = new Thread(threadTasks[i].ExecuteOne);
                }

                for (int i = 0; i < threadCount; ++i) {
                    threads[i].Start();
                }

                for (int i = 0; i < threadCount; ++i) {
                    threads[i].Join();
                }

                ShowGrid(16);
                Console.WriteLine();
            } while (prefixUnitSum < gridSize);

        }
    }
}
