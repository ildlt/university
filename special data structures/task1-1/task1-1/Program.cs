using System;
using System.Collections.Generic;
using System.IO;

namespace task1_1
{
    class Program
    {
        public static void ReadStartState(string[] s, ulong limit, List<ulong> a)
        {
            for (ulong i = 0; i < limit; i++)
            {
                a.Add(UInt64.Parse(s[i]));
            }
        }   

        public static ulong Transform(List<ulong> a)
        {
            ulong result = 0;
            int end = a.Count - 1;
            for (int i = end; i > 0; i--)
            {
                int t = end - i;
                ulong g = (ulong)Math.Pow(2, t);
                result += a[i] * g;
            }
            return result;
        }

        //public static ulong CustomPower(ulong a, ulong b)
        //{
        //    ulong result = 1;
        //    while (b > 0)
        //    {
        //        result = a * result;
        //        b--;
        //    }
        //    return result;
        //}

        //////////////////////////// ТУТ ПРОБЛЕМА
        public static List<ulong> ToBinary(ulong a, ulong b)
        {
            List<ulong> result = new List<ulong>();
            for (ulong i = 0; i < b; i++)
            {
                result.Add((a / (ulong)Math.Pow(2, i)));
            }
            return result;
        }
        /////////////////////////////

        public static List<ulong> getDiff(List<ulong> start_state, List<ulong> end_state, List<ulong> diff, ulong limit)
        {
            for (int i = 0; i < Convert.ToInt32(limit); i++)
            {
                diff.Add(end_state[i] - start_state[i]);
            }
            return diff;
        }

        public static ulong[] CalcDiff(List<ulong> a)
        {
            ulong[] result = new ulong[2];
            for (int i = 0; i < a.Count; i++)
            {
                if (a[i] > 0)
                {
                    result[0] += a[i];
                    result[1] += 1;
                }
            }
            return result;
        }

        public static ulong Gcd(ulong a, ulong b)
        {
            while (a != 0 && b != 0)
            {
                if (a > b)
                {
                    a = a % b;
                }
                else
                {
                    b = b % a;
                }
            }

            return a + b;
        }

    static void Main(string[] args)
        {
            string textFile = @"C:\Users\Alexis\ebalrot2.txt";

            List<ulong> start_state = new List<ulong>();
            ulong start_value = 0;
            List<ulong> end_state = new List<ulong>();
            ulong end_value = 0;
            List<ulong> diff = new List<ulong>();
            ulong[] answer = new ulong[2];

            //////////////////////////////// Ввод из файла

            string[] lines = File.ReadAllLines(textFile);

            ulong limit = Convert.ToUInt64(lines[0]);

            string[] s = lines[1].Split(' ');

            ReadStartState(s, limit, start_state);

            ulong number = Convert.ToUInt64(lines[2]);

            ///////////////////////////// Ввод из консоли

            //ulong limit = Convert.ToUInt64(Console.ReadLine());

            //string[] s = Console.ReadLine().Split(' ');

            //ReadStartState(s, limit, start_state);

            //ulong number = Convert.ToUInt64(Console.ReadLine());

            start_value = Transform(start_state);

            end_value = start_value + number;

            end_state = ToBinary(end_value, limit);
            start_state = ToBinary(start_value, limit);

            getDiff(start_state, end_state, diff, limit);

            answer = CalcDiff(diff);

            ulong gcd = Gcd(answer[0], number);

            Console.WriteLine(answer[1]);
            Console.WriteLine(answer[0] / gcd + "/" + number / gcd);
        }
    }
}
