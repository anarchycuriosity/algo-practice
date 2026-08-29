#include <bits/stdc++.h>
using namespace std;

struct State
{
    int rides;       // 已经用了多少趟
    long long load;  // 最后一趟目前重量
};

int main()
{
    int n;
    long long W;
    cin >> n >> W;

    vector<long long> cow(n);

    for (int i = 0; i < n; i++)
    {
        cin >> cow[i];
    }

    int total = 1 << n;

    vector<State> dp(total, {n + 1, 0});

    // 当前第一趟电梯为空
    dp[0] = {1, 0};

    for (int mask = 0; mask < total; mask++)
    {
        for (int i = 0; i < n; i++)
        {
            // 牛 i 已经运走了
            if (mask & (1 << i)) continue;

            int next = mask | (1 << i);

            State cur;

            // 当前电梯还能塞下
            if (dp[mask].load + cow[i] <= W)
            {
                cur = {dp[mask].rides, dp[mask].load + cow[i]};
            }
            else
            {
                // 开新的一趟
                cur = {dp[mask].rides + 1, cow[i]};
            }

            // 先比较趟数
            if (cur.rides < dp[next].rides)
            {
                dp[next] = cur;
            }
            // 趟数一样，最后一趟越轻越好
            else if (cur.rides == dp[next].rides && cur.load < dp[next].load)
            {
                dp[next] = cur;
            }
        }
    }

    cout << dp[total - 1].rides << '\n';

    return 0;
}