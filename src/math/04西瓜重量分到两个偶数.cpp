#include <bits/stdc++.h>
// 这题提醒要注意边界情况
int w;
int a, b;
const int MAXSIZE = 100;
bool judge()
{
    if (w % 2 != 0)
    {
        return false;
    }
    for (int i = 2; i <= w / 2; i += 2)
    {
        if ((w - i) % 2 == 0)
        {
            a = i;
            b = w - i;
            return true;
        }
    }
    return false;
}
int main()
{
    std::cin >> w;
    if (judge())
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
}