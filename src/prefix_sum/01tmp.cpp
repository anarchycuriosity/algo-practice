#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> P(M);

    for (int i = 0; i < M; i++)
    {
        cin >> P[i];
    }

    /*
        diff[i]表示：
        从第i个城市开始，之后的铁路使用次数增加多少

        一次旅行：
            l -> r

        会经过：
            l,l+1,...,r-1号铁路

        所以：
            diff[l]++
            diff[r]--

        最后前缀和得到每条铁路经过次数
    */

    vector<long long> diff(N + 2, 0);

    for (int i = 0; i < M - 1; i++)
    {
        int l = min(P[i], P[i + 1]);
        int r = max(P[i], P[i + 1]);

        diff[l]++;
        diff[r]--;
    }

    vector<long long> cnt(N);

    long long now = 0;

    for (int i = 1; i < N; i++)
    {
        now += diff[i];
        cnt[i] = now;
    }

    long long ans = 0;

    /*
        接下来读铁路信息

        第i行:
        A_i B_i C_i

        A:
            单次车票价格

        B:
            有卡后的单次价格

        C:
            买卡费用
    */

    for (int i = 1; i < N; i++)
    {
        long long A, B, C;

        cin >> A >> B >> C;

        long long times = cnt[i];

        long long buyTicket = times * A;

        long long buyCard = C + times * B;

        ans += min(buyTicket, buyCard);
    }

    cout << ans << "\n";

    return 0;
}