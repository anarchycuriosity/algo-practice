/*
状态下标 = 会影响未来的东西
dp的元素 = 我们想优化的东西

管道其实反而很简单
先计算理论上能飞到哪里，再把撞管子的状态杀掉。
*/
#include <bits/stdc++.h>
using namespace std;
/*
不推荐这样额外用find,而是直接用下标索引
auto it = find_if(pipes.begin(), pipes.end(),
                  [i](const Pip& pipe)
                  {
                      return pipe.p == i;
                  });

if (it != pipes.end())
{
    int l = it->l;
    int h = it->h;

    // 消掉非法高度
}
*/
struct Action
{
    int rise, fall;
};
struct Pip
{
    // int pos;
    int top;
    int bottom;
};
const int INF = 1e9;
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));  // 没点自然是0次咯
    // 这里需要区分还没有到达和初始状态
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = 0;
    }
    vector<Action> actions(n);
    for (int i = 0; i < n; i++)
    {
        cin >> actions[i].rise >> actions[i].fall;
    }
    // vector<Pip> pips(k);
    // for (int i = 0; i < k; i++)
    // {
    //     cin >> pips[i].pos >> pips[i].top >> pips[i].bottom;
    // }
    vector<bool> has_pip(n + 1, false);
    vector<Pip> pips(n + 1);
    for (int i = 0; i < k; i++)
    {
        int idx;
        cin >> idx;
        has_pip[idx] = true;
        cin >> pips[idx].bottom >> pips[idx].top;
    }
    int passed = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = actions[i - 1].rise;
        int y = actions[i - 1].fall;
        // 注意你可以飞飞飞下降但是不能下降然后飞飞飞
        // 因为上升借用了一个中间状态,假如这个中间状态本来应该是被连续点的第二次,但是如果我们是飞下来的话,那么这个次数是连续点的0次,它被干扰了
        // 所以你必须先写上升再写下降

        // 普通上升
        // for (int j = 0; j <= m; j++),小心j - x越界
        for (int j = x + 1; j <= m; j++)
        {
            // if (cur_j <= pips[cur_i].top || cur_j <= pips[cur_i].bottom)
            // {
            //     continue;
            // }
            // int i = cur_i - 1;
            // if (cur_j - actions[i].fall >= 0)
            // {
            //     dp[cur_i][cur_j] = min(dp[cur_i][cur_j], dp[i][cur_j - actions[i].fall]);
            // }
            // int cnt = 1;
            // int fly = cnt * actions[i].rise;
            // while (cur_j + fly < m)
            // {
            //     dp[cur_i][cur_j] = min(dp[cur_i][cur_j], dp[i][cur_j + fly] + cnt);
            //     cnt++;
            //     fly = cnt * actions[i].rise;
            // }
            // 上升和下降不应该放在一个单元里面处理,同时方向别搞反
            // 顺序也别反,应该是先处理上升再下降
            // 同列dp转移
            // 这一秒第一次点击
            dp[i][j] = min(dp[i][j], dp[i - 1][j - x] + 1);

            // 这一秒之前已经点击过，再点一次
            // 因为5从cnt1到3跳到8,比如说
            // 其实可以直接根据7直接到8
            dp[i][j] = min(dp[i][j], dp[i][j - x] + 1);
        }
        // 处理撞头
        for (int j = max(1, m - x + 1); j <= m; j++)  // 防御写法,防止j跑到合法高度1下面
        {
            // 注意这里的j和上面的j的逻辑其实不太一样了
            //  从上一列直接顶到天花版
            dp[i][m] = min(dp[i][m], dp[i - 1][j] + 1);
            dp[i][m] = min(dp[i][m], dp[i][j] + 1);
        }

        // 下降
        for (int j = 1; j + y <= m; j++)
        {
            dp[i][j] = min(dp[i - 1][j + y], dp[i][j]);
        }
        // 管道过滤
        // 为什么管道过滤要单独写呢?因为在优化cnt + while的时候,你需要用到一些中介的状态
        // 而这个状态虽然是违法的,比如 7<j < 10,但是我其实是从5连续跳几次跳到7,如果就这样continue的话,对cnt +
        // while连跳的优化就错误了
        if (has_pip[i])
        {
            bool alive = false;
            for (int j = 1; j <= m; j++)
            {
                if (j <= pips[i].bottom || j >= pips[i].top)
                {
                    dp[i][j] = INF;
                }
                if (dp[i][j] < INF)
                {
                    alive = true;
                }
            }
            if (!alive)
            {
                cout << 0 << "\n" << passed;
                return 0;
            }
            passed++;
        }
    }
    int ans = INF;
    for (int j = 1; j <= m; j++)
    {
        ans = min(ans, dp[n][j]);
    }
    cout << 1 << "\n" << ans;
}