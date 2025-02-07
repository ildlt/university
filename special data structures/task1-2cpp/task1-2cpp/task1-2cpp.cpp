#include <iostream>
#include <stack>
#include <string>
using namespace std;

void customPush(int value, stack<pair<int, int>>& leftStack, stack<pair<int, int>>& rightStack) {
    if (leftStack.empty()) {
        leftStack.push(pair<int, int> (value, value));
    }
    else {
        pair<int, int> current = leftStack.top();
        int minStack = current.second;
        leftStack.push(pair<int, int> (value, min(value, minStack)));
    }
}

void balanceStacks(stack<pair<int, int>>& leftStack, stack<pair<int, int>>& rightStack) {
    stack<pair<int, int>> bufferStack;
    int count = leftStack.size() / 2;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            pair<int, int> current = leftStack.top();
            leftStack.pop();
            bufferStack.push(current);
        }

        while (!leftStack.empty()) {
            pair<int, int> current = leftStack.top();
            int key = current.first;
            leftStack.pop();
            customPush(key, rightStack, leftStack);
        }

        while (!bufferStack.empty()) {
            pair<int, int> current = bufferStack.top();
            int key = current.first;
            bufferStack.pop();
            customPush(key, leftStack, rightStack);
        }
    }
    else {
        pair<int, int> current = leftStack.top();
        leftStack.pop();
        rightStack.push(current);
    }
}

void customPop(string direction, stack<pair<int, int>>& leftStack, stack<pair<int, int>>& rightStack) {
    if (direction == "L") {
        if (leftStack.empty()) {
            balanceStacks(rightStack, leftStack);
            leftStack.pop();
        }
        else {
            leftStack.pop();
        }
    }

    if (direction == "R") {
        if (rightStack.empty()) {
            balanceStacks(leftStack, rightStack);
            rightStack.pop();
        }
        else {
            rightStack.pop();
        }
    }
}

int getMin(stack<pair<int, int>>& leftStack, stack<pair<int, int>>& rightStack) {
    int minAll = -1;

    if (leftStack.empty() && !rightStack.empty()) {
        pair<int, int> current = rightStack.top();
        minAll = current.second;
    }

    if (!leftStack.empty() && rightStack.empty()) {
        pair<int, int> current = leftStack.top();
        minAll = current.second;
    }

    if (!leftStack.empty() && !rightStack.empty()) {
        pair<int, int> currentL = leftStack.top();
        int minL = currentL.second;
        pair<int, int> currentR = rightStack.top();
        int minR = currentR.second;
        minAll = min(minL, minR);
    }

    return minAll;
}

int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    string numberof;
    getline(cin, numberof);
    int limit = stoi(numberof);
    string command;
    string action;
    string direction;

    stack<pair<int, int>> leftStack;
    stack<pair<int, int>> rightStack;

    for (int i = 0; i < limit; i++)
    {
        getline(cin, command);
        action = command.substr(0, 1);
        direction = command.substr(1, 1);
        if (action == "+") {
            int end = command.length();
            int value = stoi(command.substr(3, end - 3));
            if (direction == "L") {
                customPush(value, leftStack, rightStack);
            }
            if (direction == "R") {
                customPush(value, rightStack, leftStack);
            }
        }
        if (action == "-") {
            customPop(direction, leftStack, rightStack);
        }

        int t = getMin(leftStack, rightStack);
        cout << t << "\n";
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

//using System;
//using System.Collections;
//using System.Collections.Generic;
//
//namespace task1_2
//{
//    class Program
//    {
//

//

//

//

//
//        static void Main()
//        {
//            //string textFile = @"C:\Users\Alexis\test.txt";
//            //string[] lines = File.ReadAllLines(textFile);
//            //int limit = Convert.ToInt32(lines[0]);
//            //Stack<KeyValuePair<int, int>> leftStack = new Stack<KeyValuePair<int, int>>();
//            //Stack<KeyValuePair<int, int>> rightStack = new Stack<KeyValuePair<int, int>>();
//            //for (int i = 1; i < limit + 1; i++)
//            //{
//            //    string command = lines[i];
//            //    string action = command.Substring(0, 1);
//            //    string direction = command.Substring(1, 1);
//            //    if (action == "+")
//            //    {
//            //        int end = command.Length;
//            //        int value = Convert.ToInt32(command.Substring(3, end - 3));
//            //        if (direction == "L")
//            //        {
//            //            customPush(value, ref leftStack, ref rightStack);
//            //        }
//            //        if (direction == "R")
//            //        {
//            //            customPush(value, ref rightStack, ref leftStack);
//            //        }
//            //    }
//            //    if (action == "-")
//            //    {
//            //        customPop(direction, ref leftStack, ref rightStack);
//            //    }
//
//            //    int t = getMin(ref leftStack, ref rightStack);
//            //    Console.WriteLine(t);
//            //}
//
//

//        }
//    }
//}
