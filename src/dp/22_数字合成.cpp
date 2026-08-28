#include <bits/stdc++.h>
using namespace std;
/*
所以它其实更像：

区间 DP + 可行性判定

而不是纯粹：

区间 DP + 最优化。

DP 状态必须保存足以判断未来转移的信息,而不是答案
*/
int main()
{
    int N;
    cin >> N;
    int ans = 0;
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++)
    {
        cin >> dp[i][i];
        ans = max(dp[i][i], ans);  // 这个得写,万一无论怎么合成都不如那个最大的数
    }
    for (int len = 2; len <= N; len++)
    {
        for (int start = 1; start + len - 1 <= N; start++)
        {
            for (int k = start; k < start + len - 1; k++)
            {
                if (dp[start][k] != 0 && dp[start][k] == dp[k + 1][start + len - 1])  // 容易漏掉0这个判断
                {
                    dp[start][start + len - 1] = dp[start][k] + 1;
                    ans = max(ans, dp[start][k] + 1);
                }
            }
        }
    }
    cout << ans;
}