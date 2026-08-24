#include <bits/stdc++.h>
using namespace std;
#define ll long long
/*
状态转移方程,当前的i的数据从过去的i - k经过一个代价为k的选择而来,这里的i不一定是一维的
dp[i][m] = 用了 i 秒、剩余 m 点魔法时，最远能走多远
这是最正统的dp,数据向量化.
再乘一个魔法值维度，就很不划算了。
所以接下来真正有意思的是：
能不能把“魔法值”这个状态维度消掉？
一个非常关键的性质：跑步不影响魔法.所以跑步放在哪里其实都没有关系,所以不妨把跑步放后面
*/

int main()
{
    int M, S, T;
    cin >> M >> S >> T;
    int magic_D = 0;
    int best_D = 0;
    for (int t = 1; t <= T; t++)  // 用t遍历,消除了dp数组的t的维度
    // 这里建议从1开始,因为当前t经历了一次抉择,产生了代价
    {
        /*
        我觉得这个很关键,也就是跑步只可能和回蓝取舍,如果就剩一点距离,就别回蓝的直接润
        这个bestdistance相当于预先瞄准
        */
        if (M >= 10)  // 等于号别忘记了
        {
            magic_D += 60;
            M -= 10;
        }
        else
        {
            M += 4;
        }

        best_D = max(best_D + 17, magic_D);
        if (best_D >= S)
        {
            cout << "Yes\n" << t;
            return 0;
        }
    }
    cout << "No\n" << best_D;
}