using System;
using System.Collections;
using System.Collections.Generic;

namespace task1_2
{
    class Program
    {
        
        public static void customPush(int value, ref Stack<KeyValuePair<int, int>> leftStack, ref Stack<KeyValuePair<int, int>> rightStack)
        {   
            if (leftStack.Count == 0)
            {
                leftStack.Push(new KeyValuePair<int, int>(value, value));
            } else
            {
                KeyValuePair<int, int> current = leftStack.Peek();
                int min = current.Value;
                leftStack.Push(new KeyValuePair<int, int>(value, Math.Min(value, min)));
            }
        }

        public static void customPop(string direction, ref Stack<KeyValuePair<int, int>> leftStack, ref Stack<KeyValuePair<int, int>> rightStack)
        {
            if (direction == "L")
            {
                if (leftStack.Count == 0)
                {
                    balanceStacks(ref rightStack, ref leftStack);
                    leftStack.Pop();
                } else
                {
                    leftStack.Pop();
                }
            }
            if (direction == "R")
            {
                if (rightStack.Count == 0)
                {
                    balanceStacks(ref leftStack, ref rightStack);
                    rightStack.Pop();
                }
                else
                {
                    rightStack.Pop();
                }
            }
        }

        public static void balanceStacks(ref Stack<KeyValuePair<int, int>> leftStack, ref Stack<KeyValuePair<int, int>> rightStack)
        {
            Stack<KeyValuePair<int, int>> bufferStack = new Stack<KeyValuePair<int, int>>();
            int count = leftStack.Count / 2;
            if (count > 0)
            {            
                for (int i = 0; i < count; i++)
                {
                    KeyValuePair<int, int> current = leftStack.Peek();
                    leftStack.Pop();
                    bufferStack.Push(current);
                }
                //for (int i = 0; i < count; i++)
                while(leftStack.Count > 0)
                {
                    KeyValuePair<int, int> current = leftStack.Peek();
                    int key = current.Key;
                    leftStack.Pop();
                    customPush(key, ref rightStack, ref leftStack);
                }
                //for (int i = 0; i < count; i++)
                while(bufferStack.Count > 0)
                {
                    KeyValuePair<int, int> current = bufferStack.Peek();
                    int key = current.Key;
                    bufferStack.Pop();
                    customPush(key, ref leftStack, ref rightStack);
                }
            } else
            {
                KeyValuePair<int, int> current = leftStack.Peek();
                leftStack.Pop();
                rightStack.Push(current);
            }
        }

        public static int getMin(ref Stack<KeyValuePair<int, int>> leftStack, ref Stack<KeyValuePair<int, int>> rightStack)
        {
            int min = -1;
            if (leftStack.Count == 0 & rightStack.Count != 0)
            {
                KeyValuePair<int, int> current = rightStack.Peek();
                min = current.Value;
            }

            if (leftStack.Count != 0 & rightStack.Count == 0)
            {
                KeyValuePair<int, int> current = leftStack.Peek();
                min = current.Value;
            }

            if (leftStack.Count != 0 & rightStack.Count != 0)
            {
                KeyValuePair<int, int> currentL = leftStack.Peek();
                int minL = currentL.Value;
                KeyValuePair<int, int> currentR = rightStack.Peek();
                int minR = currentR.Value;
                min = Math.Min(minL, minR); 
            }

            return min;
        }

        static void Main()
        {
            //string textFile = @"C:\Users\Alexis\test.txt";
            //string[] lines = File.ReadAllLines(textFile);
            //int limit = Convert.ToInt32(lines[0]);
            //Stack<KeyValuePair<int, int>> leftStack = new Stack<KeyValuePair<int, int>>();
            //Stack<KeyValuePair<int, int>> rightStack = new Stack<KeyValuePair<int, int>>();
            //for (int i = 1; i < limit + 1; i++)
            //{
            //    string command = lines[i];
            //    string action = command.Substring(0, 1);
            //    string direction = command.Substring(1, 1);
            //    if (action == "+")
            //    {
            //        int end = command.Length;
            //        int value = Convert.ToInt32(command.Substring(3, end - 3));
            //        if (direction == "L")
            //        {
            //            customPush(value, ref leftStack, ref rightStack);
            //        }
            //        if (direction == "R")
            //        {
            //            customPush(value, ref rightStack, ref leftStack);
            //        }
            //    }
            //    if (action == "-")
            //    {
            //        customPop(direction, ref leftStack, ref rightStack);
            //    }

            //    int t = getMin(ref leftStack, ref rightStack);
            //    Console.WriteLine(t);
            //}


            int limit = Convert.ToInt32(Console.ReadLine());
            Stack<KeyValuePair<int, int>> leftStack = new Stack<KeyValuePair<int, int>>();
            Stack<KeyValuePair<int, int>> rightStack = new Stack<KeyValuePair<int, int>>();
            for (int i = 0; i < limit; i++)
            {
                string command = Console.ReadLine();
                string action = command.Substring(0, 1);
                string direction = command.Substring(1, 1);
                if (action == "+")
                {
                    int end = command.Length;
                    int value = Convert.ToInt32(command.Substring(3, end - 3));
                    if (direction == "L")
                    {
                        customPush(value, ref leftStack, ref rightStack);
                    }
                    if (direction == "R")
                    {
                        customPush(value, ref rightStack, ref leftStack);
                    }
                }
                if (action == "-")
                {
                    customPop(direction, ref leftStack, ref rightStack);
                }

                int t = getMin(ref leftStack, ref rightStack);
                Console.WriteLine(t);
            }
        }
    }
}
