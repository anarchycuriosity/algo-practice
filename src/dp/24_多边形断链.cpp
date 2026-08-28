#include <bits/stdc++.h>
using namespace std;
/*
负数乘法的大坑
一个现在看起来很差的负数，会因为未来乘另一个负数而变成最优答案。
*/
struct Unit
{
    char head;
    int val;
    char butt;
};
const int NEG_INF = -1e9;
const int INF = 1e9;
int main()
{
    int n;
    cin >> n;
    int cpn = 2 * n;
    vector<Unit> polygon(cpn + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> polygon[i].head;
        cin >> polygon[i].val;
    }
    polygon[n].butt = polygon[1].head;
    for (int i = 1; i < n; i++)
    {
        polygon[i].butt = polygon[i + 1].head;
    }
    for (int i = 1; i <= n; i++)
    {
        polygon[i + n].butt = polygon[i].butt;
        polygon[i + n].head = polygon[i].head;
        polygon[i + n].val = polygon[i].val;
    }
    vector<pair<int, int>> pre_ansers;  // 第一个放序列,第二个放score
    int ans = NEG_INF;
    for (int cut = 1; cut <= n; cut++)
    {
        int score = 0;
        int cut_end = cut + n - 1;
        vector<vector<int>> dp(cpn + 1, vector<int>(cpn, NEG_INF));  // 这里是cpn而不是n
        vector<vector<int>> min_dp(cpn + 1, vector<int>(cpn, INF));  // 这里是最小值dp,所以应该初始化为INF
        for (int i = cut; i <= cut_end; i++)
        {
            dp[i][i] = polygon[i].val;
        }
        for (int i = cut; i <= cut_end; i++)
        {
            min_dp[i][i] = polygon[i].val;
        }
        for (int len = 2; len <= n; len++)
        {
            for (int start = cut; start <= cut_end - len + 1; start++)
            {
                int end = start + len - 1;
                for (int k = start; k < end; k++)
                {
                    if (dp[start][k] == NEG_INF || dp[k + 1][end] == NEG_INF)
                    {
                        continue;
                    }
                    if (min_dp[start][k] == INF || min_dp[k + 1][end] == INF)
                    {
                        continue;
                    }
                    if (polygon[k + 1].head == 't')
                    {
                        dp[start][end] = max(dp[start][end], dp[start][k] + dp[k + 1][end]);
                        min_dp[start][end] = min(min_dp[start][end], min_dp[start][k] + min_dp[k + 1][end]);
                    }
                    else
                    {
                        int a = dp[start][k] * dp[k + 1][end];
                        int b = dp[start][k] * min_dp[k + 1][end];
                        int c = min_dp[start][k] * dp[k + 1][end];
                        int d = min_dp[start][k] * min_dp[k + 1][end];

                        dp[start][end] = max({dp[start][end], a, b, c, d});
                        min_dp[start][end] = min({min_dp[start][end], a, b, c, d});
                        // dp[start][end] = max(dp[start][end], dp[start][k] * dp[k + 1][end]);
                    }
                    // score = max(score, dp[start][end]);
                }
            }
        }
        score = dp[cut][cut_end];
        ans = max(ans, score);
        pre_ansers.push_back({cut, score});
    }
    cout << ans << "\n";
    for (int i = 0; i < pre_ansers.size(); i++)
    {
        if (pre_ansers[i].second == ans)
        {
            cout << pre_ansers[i].first << " ";
        }
    }
}