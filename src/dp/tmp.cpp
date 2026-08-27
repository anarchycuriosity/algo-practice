#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Action
{
    int rise;
    int fall;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Action> actions(n);

    for (int i = 0; i < n; i++)
    {
        cin >> actions[i].rise >> actions[i].fall;
    }

    // 没有管道时：
    // 0 < j < m + 1
    // 所有 1~m 都合法
    vector<int> low(n + 1, 0);
    vector<int> high(n + 1, m + 1);
    vector<bool> hasPipe(n + 1, false);

    for (int i = 0; i < k; i++)
    {
        int p, l, h;
        cin >> p >> l >> h;

        low[p] = l;
        high[p] = h;
        hasPipe[p] = true;
    }

    /*
        dp[i][j]:
        到达横坐标 i、高度 j 的最少点击次数
    */
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));

    // 初始可以从任意合法高度出发
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    int passed = 0;

    for (int i = 1; i <= n; i++)
    {
        int x = actions[i - 1].rise;
        int y = actions[i - 1].fall;

        // ------------------------
        // 1. 点击，上升
        // ------------------------

        for (int j = x + 1; j <= m; j++)
        {
            // 这一秒第一次点击
            dp[i][j] = min(dp[i][j], dp[i - 1][j - x] + 1);

            // 这一秒之前已经点击过，再点一次
            dp[i][j] = min(dp[i][j], dp[i][j - x] + 1);
        }

        // ------------------------
        // 2. 撞到天花板 m
        // ------------------------

        for (int j = max(1, m - x + 1); j <= m; j++)
        {
            // 从上一列直接点到天花板
            dp[i][m] = min(dp[i][m], dp[i - 1][j] + 1);

            // 当前这一秒已经点过，再点到天花板
            dp[i][m] = min(dp[i][m], dp[i][j] + 1);
        }

        // ------------------------
        // 3. 一次都不点击，下降
        // ------------------------

        for (int j = 1; j + y <= m; j++)
        {
            dp[i][j] = min(dp[i][j], dp[i - 1][j + y]);
        }

        // ------------------------
        // 4. 管道过滤
        // ------------------------

        bool alive = false;

        for (int j = 1; j <= m; j++)
        {
            if (j <= low[i] || j >= high[i])
            {
                dp[i][j] = INF;
            }

            if (dp[i][j] < INF)
            {
                alive = true;
            }
        }

        // 已经没有任何高度能活下来
        if (!alive)
        {
            cout << 0 << '\n';
            cout << passed << '\n';
            return 0;
        }

        // 成功通过当前位置的管道
        if (hasPipe[i])
        {
            passed++;
        }
    }

    int ans = INF;

    for (int j = 1; j <= m; j++)
    {
        ans = min(ans, dp[n][j]);
    }

    cout << 1 << '\n';
    cout << ans << '\n';

    return 0;
}