#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> p1(n);

    for (int i = 0; i < n; i++)
    {
        cin >> p1[i];
    }

    // 数字范围是 1~n，所以必须 n+1
    vector<int> pos(n + 1);

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        pos[x] = i;  // 下标是数字，元素是它在 p2 中的位置
    }

    // 把 p1 的“元素值”转换成“这个元素在 p2 中的位置”
    for (int i = 0; i < n; i++)
    {
        p1[i] = pos[p1[i]];
    }

    // 普通 O(n^2) LIS
    vector<int> dp(n, 1);

    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (p1[i] > p1[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
}