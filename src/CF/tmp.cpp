#include <bits/stdc++.h>
using namespace std;

/*
写法	含义
x >> k	x整体右移k位，相当于去掉低k位
x << k	左移k位，相当于乘 2^k
1 << bit	生成只有第bit位为1的数
(x >> bit) & 1	取x的第bit位
a & b	按位与，两个位置都是1才为1
*/
/*


*/

/*
    这题需要判断：

    一个区间 [l,r) 中的元素，
    是否已经属于它应该属于的区间。

    例如：

    原数组:
        index: 0 1 2 3
        value: 1 3 2 4

    排序后:
        1 2 3 4

    如果左半区间 [0,2)
    原来有 {1,3}
    排序后应该有 {1,2}

    那么说明：
    左半区不能自己完成排序，
    必须借助跨越当前bit的交换。


    为了快速判断区间是否相同：

    我们把每个元素映射到它在排序数组中的位置。

    例如：

    a = [1,3,2]

    sorted = [1,2,3]

    那么：

    原位置:
    0 1 2

    对应排序位置:
    0 2 1


    如果一个区间 [l,r) 的所有排序位置也都落在 [l,r)

    那么这个区间就是正确的。
*/

struct NodeInfo
{
    int ans;  // 当前区间需要的最小k
    int mn;   // 当前区间映射位置最小值
    int mx;   // 当前区间映射位置最大值
};

vector<int> pos;

/*
    判断当前区间在某一位bit下是否需要这一位

    返回：

    ans:
        当前区间答案

    mn,mx:
        这个区间所有元素对应的排序位置范围

*/
NodeInfo dfs(int l, int r, int bit)
{
    // 单个元素不用交换
    if (r - l <= 1)
    {
        return {0, pos[l], pos[l]};
    }

    /*
        找当前bit把区间切开的地方


        举例:

        bit = 2

        二进制:

        0000
        0001
        0010
        0011
        0100
        0101


        bit=2时：

        0xxx 和 1xxx 是两个区域


        (l >> bit)
        是把低bit位全部去掉

        << bit
        是再乘回来


        ((l>>bit)+1)<<bit

        就是当前区域下一个分界线
    */

    int mid = ((l >> bit) + 1) << bit;

    /*
        如果mid不在(l,r)里面

        说明整个区间这一位都是一样的

        例如:

        [0,4)

        看bit=3

        全部都是0

        所以不用管这一位
    */
    if (mid <= l || mid >= r)
    {
        NodeInfo res = dfs(l, r, bit - 1);
        return res;
    }

    /*
        当前bit把区间分成：

        [l,mid)
        [mid,r)
    */

    NodeInfo left = dfs(l, mid, bit - 1);
    NodeInfo right = dfs(mid, r, bit - 1);

    /*
        判断：

        左区间的元素是否仍然属于左区间

        因为pos保存的是：
        "这个元素排序后应该去哪里"


        如果：

        左边所有pos都在[l,mid)

        右边所有pos都在[mid,r)

        那么不用跨越当前bit。


        注意：

        不需要排序，不需要map。

        因为：

        一个长度一样的集合，
        如果所有目标位置都在这个集合里面，
        它一定完全匹配。
    */

    bool left_ok = left.mn >= l && left.mx < mid;

    bool right_ok = right.mn >= mid && right.mx < r;

    if (left_ok && right_ok)
    {
        // 当前bit不用开
        return {max(left.ans, right.ans), min(left.mn, right.mn), max(left.mx, right.mx)};
    }
    else
    {
        /*
            当前bit必须为1

            例如:

            bit=3

            那么贡献:

            1000

            即：

            1<<bit


            << 是左移

            1 << 3

            二进制:

            0001
             |
             v

            1000
        */

        return {1 << bit, min(left.mn, right.mn), max(left.mx, right.mx)};
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int n, q;
        cin >> n >> q;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        /*
            建立：

            原位置 -> 排序后位置


            pair:

            {数值, 原来的下标}

            排序后：

            第几个就是它的位置。


            这样处理重复数字不会出问题。

            例如:

            1 2 2 3

            两个2可以互换身份。
        */

        vector<pair<int, int>> v;

        for (int i = 0; i < n; i++)
        {
            v.push_back({a[i], i});
        }

        sort(v.begin(), v.end());

        pos.assign(n, 0);

        for (int i = 0; i < n; i++)
        {
            int original_index = v[i].second;

            pos[original_index] = i;
        }

        /*
            n <= 1e6

            下标最大不到2^20

            但是为了安全直接从30开始。
        */

        NodeInfo ans = dfs(0, n, 30);

        cout << ans.ans << '\n';

        /*
            easy版本 q=0

            所以后面没有update。

            hard版本需要动态维护这里的信息。
        */
    }

    return 0;
}