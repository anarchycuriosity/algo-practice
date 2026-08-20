#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct Interval
{
    ll l, r;
};
bool comp(const Interval& x, const Interval& y)
{
    if (x.l != y.l)
    {
        return x.l < y.l;
    }
    else
    {
        return x.r > y.r;
    }
}
int main()
{
    ll L, R;
    int n;
    cin >> L >> R;
    cin >> n;
    vector<Interval> vec(n);
    for (auto& [left, right] : vec)
    {
        ll x, y;
        cin >> x >> y;
        left = min(x, y);
        right = max(x, y);  // 注意题目给的端点不一定说明x一定小于y
    }
    sort(vec.begin(), vec.end(), comp);
    // ll cur = LLONG_MIN;
    ll cur = L;  // 应该是L而不是最小值
    int count = 0;
    int index = 0;
    // 这里似乎不需要担心接不上的问题,但我觉得最好有个判断
    // 这个循环有点难写,需要先找能够接的上当前的cur的,同时又不能太频繁的改变cur的值
    while (cur < R)
    {
        ll far = cur;
        // while (index < n && vec[index].l <= cur)
        while (index < n && vec[index].l <= cur)
        {
            far = max(far, vec[index].r);
            index++;
        }
        // 这里不需要记录变化的那个左端点的值,因为只要能接上就好了,别的不重要
        if (far == cur)
        {
            cout << -1;
            return 0;
        }
        count++;
        cur = far;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     if (cur >= R)
    //     {
    //         break;
    //     }
    //     if (cur < vec[i].r)
    //     {
    //         for (int j = i; j < n; j++)
    //         {
    //             if (vec[i].l <= cur)
    //             {
    //                 cur = max(cur, vec[i].r);
    //             }
    //         }
    //         count++;
    //     }
    // }
    cout << count;
}