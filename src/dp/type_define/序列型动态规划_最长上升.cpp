#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<ll> seq(n);
    vector<ll> dp(n, 1);
    for (int i = 0; i < n; i++)
    {
        cin >> seq[i];
    }
    ll ans = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (seq[i] > seq[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
                ans = max(ans, dp[i]);
            }
        }
    }
    cout << ans;
}