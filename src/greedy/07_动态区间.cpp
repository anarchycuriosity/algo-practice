/*
之前那个心理平衡者的问题,虽然每个人都有一个预期,但是也很容易排序好,就是邻项不断交换,按照优先排小的就对
但是这个不太一样的是,每个人的预期是一个区间,而不是非黑即白
在任意时刻 K，所有 Li ≤K 的人都已经“可用”
我们希望让Ri小的人先进入,因为它很急,Ri大的人也晚一点
但是好像有点复杂的是,随着人的加入,先前符合Li条件而加入的人可能会想quit,难的是怎么处理这个点
拿心理平衡者来说,都是排序好最优选择,一直无脑拿直到达到条件就好了,而且那个人也不会退出
不对,这题没那么难,因为是报出现在已经参与的人数,草没认真读题
*/
/*
应该从所有已经可加入的人里面找 r 最小的人，而不是直接取排序后的下一个人。
你自己画一下区间就好了,我们只在可以加入的人里面考虑,你都不加入我考虑什么,等能加入的人加入了当前人数增加再考虑
如果容易过期的人容易进入,也就是l更小,那么它进去了其实更有利于不那么容易的人进入
如果容易过期的人不容易进入,也就是l更大,那么它进不进去其实无所谓,因为其他人本来就更容易进入
至于怎么快速找到 Ri 最小的可用人——那是实现层面的问题，
用合适的数据结构维护即可，但贪心策略本身已经确定下来了。
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Interval
{
    ll l, r;
    int ind;
};
bool comp(const Interval& x, const Interval& y)
{
    if (x.l != y.l)
    {
        return x.l < y.l;
    }
    // else
    // {
    //     return x.r < y.r;
    // }
}
struct comp
{
    bool operator()(const Interval& x, const Interval& y) const { return x.r > y.r; }
};
int main()
{
    int n;
    cin >> n;
    vector<Interval> intervals;
    for (int i = 0; i < n; i++)
    {
        Interval interval;
        ll left, right;
        cin >> left >> right;
        interval.l = min(left, right);
        interval.r = max(left, right);
        interval.ind = i + 1;
        intervals.push_back(interval);
    }
    sort(intervals.begin(), intervals.end(), comp);
    vector<int> ans;
    int count = 0;
    int i = 0;
    // i 只往右走、每轮只扫描新解锁的人”这个做法，依赖于数组已经按照 l 单调排序,但是r的排序不是很重要
    while (true)
    {
        // if (intervals[i].l > count || i == n)顺序很重要,不然会短路,这是反面教材
        // int i = 0;

        // 不能简单的决定拿不拿,必须建立一个候选池子,而这个候选池子能够自己整理,i扫过了就可以进去,而不要让i扫很多次
        // 没错就是小根堆
        ll emergen = LLONG_MAX;
        ll tar = -1;
        while (i < n && intervals[i].l <= count)
        {
            if (emergen > intervals[i].r)
            {
                emergen = min(emergen, intervals[i].r);
                tar = intervals[i].ind;
            }
            i++;
        }
        if (tar == -1)
        {
            break;
        }
        count++;
        ans.push_back(tar);

        // 因为排序好了,找到的第一个肯定是最急的
    }
    cout << count << "\n";
    // for (auto& num : ans)
    // {
    //     cout << num << " ";
    // }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
