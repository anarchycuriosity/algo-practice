/*
买卡可以重复用，但是买票只能用一次
如果会反复来这段，买卡会更划算

需要先专门用一个数组去存次数，不能一直更新value，因为买卡的影响是长期的，所以要提前规划而不是动态规划
因为这里只能一段段走，所以涉及了区间求和
前缀和解决的问题：频繁查询区间总和太慢。
差分解决的问题：频繁修改区间太慢。

这里的输入是区间的l和r，每次走一个区间，因为这里是频繁修改区间，所以我们用差分数组
在进入区间的时候，区间内的所有片段++，出去后的所有片段--
对应差分就是入口++，出口--
*/
#define ll long long
#include <bits/stdc++.h>

int main()
{
    ll N, M;
    std::cin >> N >> M;
    std::vector<ll> edges(M);
    std::vector<ll> diffs(N + 1, 0);
    for (size_t i = 0; i < M; i++)
    {
        std::cin >> edges[i];
    }
    for (size_t i = 0; i < M - 1; i++)
    {
        ll l = std::min(edges[i], edges[i + 1]);
        ll r = std::max(edges[i], edges[i + 1]);
        diffs[l]++;
        diffs[r]--;
    }
    std::vector<ll> cnt(N);  // 这是数边的个数，所以总数是n-1
    ll count = 0;
    for (size_t i = 1; i < N; i++)  // 用差分数组拿到修改的数据后再做前缀和运算拿到正常表去查
    {
        count += diffs[i];
        cnt[i] = count;
    }
    ll res = 0;
    for (ll i = 1; i < N; i++)
    {
        ll a, b, c;
        std::cin >> a >> b >> c;
        ll card_cost = cnt[i] * b + c;
        if (cnt[i] != 0)
        {
            res += std::min(cnt[i] * a, card_cost);
        }
    }
    std::cout << res;
}