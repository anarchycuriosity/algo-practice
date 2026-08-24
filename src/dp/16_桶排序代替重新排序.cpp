/*
这题真正值得记住的不是“四维 DP”

我觉得你第一反应想到“排列顺序”，其实非常正常，因为题目表面就在问：

这些牌按照什么顺序打最好？

但 DP 的切入点恰恰是：

哪些不同的历史，在未来看来其实完全等价？

全排列记录的是过去每一步精确用了哪张牌。
但问题在于,我根本不需要知道这么精确的历史.
当剩余卡片一样的时候,其实过去的那些排序都不重要了,我们只需要保留最大的那一个
核心最小单元,也就是for循环的最小单元,也就是在排重,所以for的四个维度必须代表未来的选择分支是一致的,也就是4张牌的数量是一致的
四层 for 循环枚举的最小单元，其实是一个“状态”；而状态压缩的核心，就是把所有“未来完全等价”的历史排重、合并。
注意,乌龟棋很幸运,因为如果使用的牌的数量一致的话,那么距离也是一致的,反例参照飞行棋和传送
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int dp[41][41][41][41];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> board(N);
    for (int i = 0; i < N; i++)
    {
        cin >> board[i];
    }
    vector<int> cnt(5);
    for (int i = 0; i < M; i++)
    {
        int step = 0;
        cin >> step;
        cnt[step]++;
    }
    dp[0][0][0][0] = board[0];
    for (int i = 0; i <= cnt[1]; i++)
    {
        for (int j = 0; j <= cnt[2]; j++)
        {
            for (int k = 0; k <= cnt[3]; k++)
            {
                for (int l = 0; l <= cnt[4]; l++)
                {
                    int best = 0;
                    if (i == 0 && j == 0 && k == 0 && l == 0)
                    {
                        continue;
                    }
                    if (i > 0)
                    {
                        best = max(best, dp[i - 1][j][k][l]);
                    }
                    if (j > 0)
                    {
                        best = max(best, dp[i][j - 1][k][l]);
                    }
                    if (k > 0)
                    {
                        best = max(best, dp[i][j][k - 1][l]);
                    }
                    if (l > 0)
                    {
                        best = max(best, dp[i][j][k][l - 1]);
                    }
                    int loc = 1 * i + 2 * j + 3 * k + 4 * l;
                    dp[i][j][k][l] = best + board[loc];
                }
            }
        }
    }
    cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]];
}