#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int n, m;
    cin >> n >> m;
    ll dp[67][67] = {};
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i > 0)
            {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0)
            {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    cout << dp[n][m];
}