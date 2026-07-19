// 这题要找的下标比较庞大，而且我们知道范围，所以考虑二分
// 同时在范围内它是单调递增的，所以二分是ok的
// 这里补充一个数学知识，某个数整除n的结果不仅仅代表至少可以被分成几份还代表前面有几个可以被整除的数
#include <bits/stdc++.h>
#define ll long long
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    ll n, k;
    std::cin >> t;
    std::vector<ll> res;
    while (t--)
    {
        std::cin >> n >> k;
        ll left = 1;
        // ll right = 2 * 10e9;  // 上界根据极端情况得到
        ll right = 2e9;
        // n越小，就容易插入更多可以被整除的数，所以那个数会更大
        // k越大，这个要找的数显然递增
        // 所以极端就是n是2，k最大的时候，得到right
        int ans = right;
        while (left <= right)
        {
            // ll mid = (left + right) / 2;
            ll mid = left + (right - left) / 2;  // 一定要这样写，否则在某些大一点的数据就溢出了然后卡死在这个while循环
            ll count = mid - mid / n;
            if (count > k)
            {
                ans = mid;
                right = mid - 1;  // 如果没有-1的话在某些很小的边界容易出错
                // ans = right;
            }
            else if (count < k)
            {
                left = mid + 1;
            }
            else  // 第二次提交错误，虽然count是对的，但是不一定最小，不能直接break
            // 其实可以合并进上面那个，这里是为了显示错误，>=就往左边缩进可以起到一个找最小值的作用
            {
                // res.push_back(mid);
                // break;
                // 这里有个魔鬼细节，ans不能直接用新的mid赋值，因为新的mid还没有确定过，探过去了可能会出错
                ans = mid;
                right = mid - 1;
                // ans = right;
            }
        }
        res.push_back(ans);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << "\n";
    }
}