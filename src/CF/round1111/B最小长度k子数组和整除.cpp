/*
以后看到“构造正整数数组，并控制某些子数组的和”时，可以先问：

能不能先把所有数放到允许的最小值？

因为这样做有两个好处：

你知道当前总和的最低下界；
你可以把剩余差值有控制地加到少数位置。

所以“全部放 1”不是某种神秘套路，而是一个非常普通的工程思路：

先初始化到最小合法状态，再逐步补到目标
        ​

这题因为只是要找可能性，而且输出个例，所以我们肯定选择最容易构造的一个数组
对于求子数组和不能超过某个值，我们只要让手更短的子数组拿不到那个大的数就好了，也就是把“钥匙”放在远一点的地方
*/

#include <bits/stdc++.h>

int main()
{
    int n, k, m, test_count;
    // n是总长度，k是子数组最小长度，m是整除数
    std::cin >> test_count;
    std::vector<bool> judges;
    std::vector<std::vector<int>> res;
    while (test_count--)
    {
        std::cin >> n >> k >> m;
        if (k > m)
        {
            judges.push_back(false);
            std::vector<int> tmp;
            res.push_back(tmp);
            continue;
        }
        std::vector<int> vec(n, 1);
        for (int i = 0; i < vec.size(); i++)
        {
            if ((i + 1) % k == 0)
            {
                vec[i] = m - k + 1;
            }
        }
        judges.push_back(true);
        res.push_back(vec);
    }
    for (int i = 0; i < judges.size(); i++)
    {
        if (judges[i] == true)
        {
            std::cout << "YES" << "\n";
            for (int j = 0; j < res[i].size(); j++)
            {
                std::cout << res[i][j] << " ";
            }
            std::cout << "\n";
        }
        else
        {
            std::cout << "NO" << "\n";
        }
    }
}