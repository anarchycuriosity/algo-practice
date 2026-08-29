#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
/*
不同的历史，只要最后得到的“未来相关信息”相同，就合并。
现在又有一条新的历史到达 next 了。我要决定这条历史值不值得留下。
如果趟数更少或者容量更多,我就留下
cur 是一个合法方案，只是它比 dp[next] 已经保存的方案更差。
*/
#define ll long long
struct State
{
    ll rides;  // 走了几趟
    ll load;   // 已经装了多少重量
};
int main()
{
    int n, w;
    cin >> n >> w;
    vector<int> cows(n, 0);
    for (int i = 0; i < n; i++)  // 0下标,因为后面位移动都是从0开始
    {
        cin >> cows[i];
    }
    ll total = 1 << n;
    vector<State> dp(total, {n + 1, 0});  // 目前是未抵达区域,如果更小就会抵达,所以初始化为无法被触碰到的大的值n + 1
    dp[0] = {1, 0};
    /*
    例如把 rides 定义成：

已经完成的电梯趟数，不包括当前正在装的这一趟,就是0,0,否则1,1
    */
    for (int mask = 0; mask < total; mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                continue;
            }
            int next = mask | (1 << i);
            // State cur = dp[mask];  // 其实改名叫做plan会毕竟好
            State cur;  // 注意,开新的一趟之后,当前电梯的load是0!!
            if (dp[mask].load + cows[i] <= w)
            {
                // cur.load += cows[i];
                cur = {dp[mask].rides, dp[mask].load + cows[i]};
            }
            else
            {
                cur = {dp[mask].rides + 1, cows[i]};
            }

            if (dp[next].rides > cur.rides)
            {
                dp[next] = cur;
            }
            else if (dp[next].rides == cur.rides && dp[next].load > cur.load)
            {
                dp[next] = cur;
            }
        }
    }
    cout << dp[total - 1].rides;
}