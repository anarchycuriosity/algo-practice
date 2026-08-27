/*
混合背包其实就是多次选01物品,使用二进制拆分
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    int h1, h2, min1, min2;
    char sep;
    cin >> h1 >> sep >> min1 >> h2 >> sep >> min2 >> n;
    int T = h2 * 60 + min2 - h1 * 60 - min1;
    vector<int> dp(T + 1, 0);  // 没看花就是0美学值
    for (int i = 0; i < n; i++)
    {
        int t, c, p;
        cin >> t >> c >> p;
        if (p == 0)
        {
            for (int j = t; j <= T; j++)
            {
                dp[j] = max(dp[j], dp[j - t] + c);
            }
        }
        else
        {
            p = min(p, T / t);
            for (int k = 1; p > 0; k <<= 1)
            {
                int cnt = min(k, p);
                p -= cnt;
                int cost = cnt * t;
                int value = cnt * c;
                for (int j = T; j >= cost; j--)
                {
                    dp[j] = max(dp[j], dp[j - cost] + value);
                }
            }
        }
    }
    cout << dp[T];
}