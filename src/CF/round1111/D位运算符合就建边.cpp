/*
只要序列按位异或<=k就可以建双向边
对于一个连通块，只要它的边都是双向的，那么就可以随便交换，产生所有可能的排序，至于过程如何，可以暂时不去深究
这题找k一开始想的是根据n的二进制都取高位然后二分去找，但是似乎并不理想
因为每次找到k之后建边非常地困难，check的代价很大，这是可以想象的
不要去建图，只要知道它们肯定可以到达就好了
不需要把所有需要交换节点都建图，只要想到的位置都连通就好了
*/
#include <bits/stdc++.h>

struct cp
{
    int ori_ind;
    int val;
};
int main()
{
    int t;
    std::cin >> t;
    std::vector<int> res;
    while (t--)
    {
        int k;
        int n, q;
        std::cin >> n >> q;
        std::vector<cp> vec;
        for (size_t i = 0; i < n; i++)
        {
            int val;
            std::cin >> val;
            cp num{i, val};
            vec.push_back(num);
        }
        std::sort(vec.begin(), vec.end(),
                  [](cp& a, cp& b) { return a.val < b.val; });  // 比较函数必须严格弱序，所以不能写=
        // 在知道k的最大值往下排查，我们不用二分，而是用位运算去排查，这样会更少而且会符合是否能够开锁开路的判断条件
        for (size_t i = 0; i < n; i++)
        {
            // 这里开始是最小解决单元
            //
            int start = vec[i].ori_ind;
            int des = i;
            for (int digit = 31; digit >= 0; digit--)
            {
            }
        }
    }
}