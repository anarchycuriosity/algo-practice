#include <iostream>
int n, w;  // n是物品个数，w是背包容量
           // 01背包是外层物品循环，内层背包容量遍历
           // 完全背包是顺序，01背包是逆序。这很好理解，因为状态转移方程就是考虑大容量和小容量+拿着的物品，这两者的取舍
// 如果我们先从大的开始，而小的容量并没有被计算过，那么这个物品在这个容器状况下就只会被考虑一次
// 而如果从小开始计算，当我们顺序遍历到大节点的时候，肯定会考虑到小容量，而此时小容量已经被计算过一次了
#include <cmath>
#include <vector>
int main()
{
    std::cin >> n >> w;
    // w++;
    // 之前犯了一个愚蠢的错误，我以为这里w++后，之后都不需要w+1
    // 但是vector的迭代器是右开的，所以。。
    std::vector<int> weighs(n, 0);
    std::vector<int> values(n, 0);
    std::vector<int> backpack(w + 1, 0);  // 数据向量化，下标是容量，元素是当前的价值
    // 顺便聊聊背包数组初始化的问题，如果是要求不装满背包的最大价值，全部初始化为0即可
    // 而如果要求是装满背包的最大价值，首先0容量状态的背包肯定是0价值
    // 所以0下标会成为合理的出发点，而其他的状态我们要标记为不合理出发点
    // 所以要标记为-inf，为什么是负无穷呢？因为-inf有个特性，任何数+负无穷都是负无穷
    // 这个无效标记具有传染性也就是说任何从这个点出发的点都是无效的
    for (int i = 0; i < n; i++)
    {
        std::cin >> weighs[i] >> values[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int cur_cap = w; cur_cap >= weighs[i]; cur_cap--)  // 下限是到当前物品的重量哦，不要越界了
        {
            backpack[cur_cap] = std::max(backpack[cur_cap], backpack[cur_cap - weighs[i]] + values[i]);
        }
    }
    std::cout << backpack[w];
}