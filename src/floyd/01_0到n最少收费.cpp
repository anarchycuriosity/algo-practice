// 必须从有效起点出发，所以初始化起点为0，其他为无穷
#include <string.h>

#include <cmath>
#include <iostream>
const int maxn = 200;
int cost_map[maxn][maxn];
int dp[maxn];
const int inf = 1e9;
int main()
{
    int n;
    std::cin >> n;
    // 用base1吧
    // 半矩阵其实就是上对角矩阵，横竖都去掉一个元素
    // 所以i的上限会少1，j的开始会少1，
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            std::cin >> cost_map[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i] = inf;
    }
    // memset(dp, 0x3f, sizeof(dp));
    dp[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            // if (dp[i] + cost_map[i][j] < dp[j])//别搞反，i是终点，然后j遍历起点
            if (dp[j] + cost_map[j][i] < dp[i])
            {
                dp[i] = dp[j] + cost_map[j][i];
            }
        }
    }
    std::cout << dp[n];
}