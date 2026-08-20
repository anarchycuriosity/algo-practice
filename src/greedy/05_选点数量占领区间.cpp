// 如果孤立地看一个区间，左右当然没有区别；区别来自你已经处理了哪一边、未来还要处理哪一边。
// 我们首先要删除包含的大区间,因为大区间没有用
// 删完之后,剩下的区间就像阶梯一样,如果按左端点从小到大排序好,那么右端点也是从小到大排序好的
/*
所以，在 R1 放一个点，一定不差于放在 [L1,R1] 内的任何其它
位置。
放了之后，所有左端点 ≤R1 的区间都被这个点覆盖了，删掉它
们。
剩下的区间还是同样形态——继续在最小的右端点放点。
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Interval
{
    ll l;
    ll r;
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Interval> intervals(n);
    for (auto& [left, right] : intervals)
    {
        cin >> left >> right;
    }
    sort(intervals.begin(), intervals.end(), [](const auto& x, const auto& y) { return x.r < y.r; });
    int ans = 0;
    // ll point = (ll)-INFINITY;
    ll point = LLONG_MIN;
    // ll point = intervals.front().r;
    for (auto interval : intervals)
    {
        if (point < interval.l)
        {
            point = interval.r;
            ans++;
        }
    }
    cout << ans;
}