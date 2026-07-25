#include <bits/stdc++.h>

struct cp
{
    int ori_ind;  // 元素原来的下标
    int val;      // 元素值
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--)
    {
        int n, q;
        std::cin >> n >> q;

        std::vector<cp> vec(n);

        for (int i = 0; i < n; i++)
        {
            std::cin >> vec[i].val;

            // 记录元素原来的位置
            vec[i].ori_ind = i;
        }

        /*
            排序以后：

            vec[i]

            表示：
            排序后的第 i 个位置应该放什么元素

            所以：

            vec[i].ori_ind

            是这个元素原来的位置

            i

            是它最终应该去的位置
        */

        std::sort(vec.begin(), vec.end(), [](const cp& a, const cp& b) { return a.val < b.val; });

        int ans_bit = -1;

        for (int target = 0; target < n; target++)
        {
            int start = vec[target].ori_ind;

            if (start == target) continue;

            int diff = start ^ target;

            int bit = 31 - __builtin_clz(diff);

            ans_bit = std::max(ans_bit, bit);
        }

        if (ans_bit == -1)
        {
            std::cout << 0 << '\n';
        }
        else
        {
            std::cout << (1 << ans_bit) << '\n';
        }
    }

    return 0;
}