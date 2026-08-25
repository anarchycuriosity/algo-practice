#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(2 * n + 1);

    // 复制数组，断环成链
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }

    // 前缀和
    vector<int> prefix(2 * n + 1, 0);

    for (int i = 1; i <= 2 * n; i++)
    {
        prefix[i] = prefix[i - 1] + a[i];
    }

    // dpMin[l][r]：
    // 把区间 [l,r] 合并成一堆的最小代价
    //
    // dpMax[l][r]：
    // 把区间 [l,r] 合并成一堆的最大代价
    vector<vector<int>> dpMin(2 * n + 1, vector<int>(2 * n + 1, INF));

    vector<vector<int>> dpMax(2 * n + 1, vector<int>(2 * n + 1, 0));

    // 一堆本来就是一堆，不需要合并
    for (int i = 1; i <= 2 * n; i++)
    {
        dpMin[i][i] = 0;
        dpMax[i][i] = 0;
    }

    // 枚举区间长度
    for (int len = 2; len <= n; len++)
    {
        // 枚举左端点
        for (int l = 1; l + len - 1 <= 2 * n; l++)
        {
            int r = l + len - 1;

            // 整个区间的石头数量
            int sum = prefix[r] - prefix[l - 1];

            // 枚举最后一次合并的位置
            for (int k = l; k < r; k++)
            {
                dpMin[l][r] = min(dpMin[l][r], dpMin[l][k] + dpMin[k + 1][r] + sum);

                dpMax[l][r] = max(dpMax[l][r], dpMax[l][k] + dpMax[k + 1][r] + sum);
            }
        }
    }

    int minAns = INF;
    int maxAns = 0;

    // 枚举从哪里把圆环剪开
    for (int i = 1; i <= n; i++)
    {
        minAns = min(minAns, dpMin[i][i + n - 1]);
        maxAns = max(maxAns, dpMax[i][i + n - 1]);
    }

    cout << minAns << '\n';
    cout << maxAns << '\n';

    return 0;
}