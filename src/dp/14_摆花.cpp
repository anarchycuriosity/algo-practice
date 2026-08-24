/*
这里的抉择似乎有点复杂了,不只是简单的在几个动作之间选择
只使用前 i 种花，恰好摆出 j 盆花，有多少种方案。这就是dp数组的定义
如果第i种花累计摆了j盆,他本身想摆了k盆,那么ij的方法数就应该由(i-1)(j-k)累加
这其实就是 DP 一个非常典型的思想：
按照“最后一次选择是什么”把所有方案划分成互不重叠的几类。
dp[i][5]
=
dp[i-1][5]
+ dp[i-1][4]
+ dp[i-1][3]
+ dp[i-1][2];
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e6 + 7;
int main()
{
    int n, m;
    cin >> n >> m;
    int dp[105][105];
    memset(dp, 0, sizeof(dp));  // 第一层是第i种花,第二层是目前累计的多少
    // dp[1][0] = 1;
    // 花的仓库是正常计数
    dp[0][0] = 1;
    // 不要问第一层怎么初始化,而是问我的状态转移最初是从哪一个状态出发
    vector<int> limits(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> limits[i];
    }
    for (int id = 1; id <= n; id++)
    {
        for (int sum = 0; sum <= m; sum++)
        {
            for (int to_take = 0; to_take <= limits[id] && to_take <= sum;
                 to_take++)  // 这个&&容易漏,因为这个to_take需要访问数组的第2维,同时sum - to_take也要访问
            {
                dp[id][sum] += dp[id - 1][sum - to_take];
                dp[id][sum] %= mod;
            }
        }
    }
    cout << dp[n][m];
}