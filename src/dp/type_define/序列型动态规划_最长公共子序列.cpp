// 公共子序列不需要是连续的,比如挑出三个数字,它们出现的顺序一致即可
// 想办法把它转到上升,因为上升是性质,我们先锁定具体的数字目标再确定顺序,这在逻辑上更清晰一些
// 把LCS转到LIS
// 我们可以想象对齐两个齿轮,然后这个子序列的数量其实就是咬合的牙齿的数量,对齐的依据是元素一致
// 或者我们联想数据库中两个table是如何join的
// 因为p1的下标天然具有递增性,当我们从左往右遍历
// 然后我们把p1的元素换成p2的下标即可,也就是说数是什么根本不重要,我们这里不需要管数是什么,数只是胶水,接上之后没人看胶水长什么样子

#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    int n;
    cin >> n;
    // 这里是1到n,所以会越界
    vector<int> p1(n);
    vector<int> p2(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p1[i];
    }
    vector<int> pos(n + 1);
    // 每次写下标的时候想想
    // pos[p2[i]] = i;
    // 这里可没有for的i < n约束,直接访问就是容易出问题
    for (int i = 0; i < n; i++)
    {
        cin >> p2[i];
        pos[p2[i]] = i;  // 下标是数,元素是位置
    }

    for (int i = 0; i < n; i++)
    {
        p1[i] = pos[p1[i]];
    }

    // vector<int> dp(n, 1);
    // int ans = 1;
    // 传统的LIS肯定超时
    /*
    所以，对于相同长度的上升子序列：

我根本没必要保存所有方案，只需要保存“结尾最小”的那个。
    你看,原本因为LIS的是依靠i来对齐齿轮,你根本不知道下一个会不会更优,所以dp要一直迭代下去更新
    但问题是迭代结束前那些都是没有用的
    所以我们去维护tails[k],下标是长度,元素是最小结尾的那个数
    因为这里根本不需要下标了,所以可以不用for循环迭代
    一个很重要的特性:tail是严格递增的,显然更长的子序列肯定有更大的下标
    一个肌肉记忆是,看到递增考虑二分
    递增很好,因为原本的i是没有递增的,所以只能扫
   */
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < i; j++)
    //     {
    //         if (p1[i] > p1[j])
    //         {
    //             dp[i] = max(dp[i], dp[j] + 1);
    //             ans = max(ans, dp[i]);
    //         }
    //     }
    // }
    // 一般来说,数组like的东西有两个要素,上一版的dp数组里面这是索引和长度
    // 而在tail数组里面,这是长度和数,把索引优化掉了,因为索引固定原数组的索引
    // 而有索引不满足递增无法用二分,就是会慢,而且我们不是在一直构造最优的子串,而是在找那个唯一的长度的答案
    vector<int> tail;
    for (int i = 0; i < n; i++)
    {
        int cur = p1[i];
        auto it = lower_bound(tail.begin(), tail.end(), cur);
        if (it != tail.end())
        {
            *it = cur;
        }
        else
        {
            tail.push_back(cur);
        }
    }

    cout << tail.size();
}