/*
实际上应该进一步抛弃“代价/好处”的背包模板思维。
Si：改变状态坐标
Fi：改变我们正在优化的值

比如现在选一个S是6但是F是3的牛
dp[8] = max(dp[8], dp[2] - 3);这就很像01背包了其实

偏移量dp,当当前的S是负数的时候应该是从左到右遍历防止用两次
*/
#include <bits/stdc++.h>
using namespace std;
const int NEG_INF = -1e9;
const int offset = 400000;
int main()
{
    int N;
    cin >> N;
    vector<int> dp(2 * offset + 1, NEG_INF);
    dp[offset] = 0;
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int s, f;
        cin >> s >> f;
        if (s >= 0)
        {
            for (int j = 2 * offset; j >= s; j--)
            {
                if (dp[j - s] == NEG_INF)
                {
                    continue;
                }
                dp[j] = max(dp[j], dp[j - s] + f);
                if (j - offset >= 0 && dp[j] >= 0)
                {
                    ans = max(ans, j - offset + dp[j]);
                }
            }
        }
        else
        {
            for (int j = 0; j <= 2 * offset + s; j++)  // 这里是+s,不然就越界了
            {
                if (dp[j - s] == NEG_INF)
                {
                    continue;
                }
                dp[j] = max(dp[j], dp[j - s] + f);
                if (j - offset >= 0 && dp[j] >= 0)
                {
                    ans = max(ans, j - offset + dp[j]);
                }
            }
        }
    }
    cout << ans;
}