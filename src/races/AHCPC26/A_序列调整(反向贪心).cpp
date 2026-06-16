// 这题思路其实和电梯按钮就是一样的
#include <iostream>
#include <stack>
#include <vector>
int main()
{
    int m;
    std::cin >> m;
    std::stack<char> ops;
    int count = 0;
    while (m > 3)  // 让它最多卡到2那里，因为要求字母序列最小，所以一开始最好给A
    {
        if (m % 2 == 0)
        {
            count++;
            m = m >> 1;
            ops.push('B');
        }
        else
        {
            count++;
            m = m - 1;
            ops.push('A');
        }
    }
    count++;
    ops.push('A');

    while (!ops.empty())
    {
        std::cout << ops.top();
        ops.pop();
    }
}