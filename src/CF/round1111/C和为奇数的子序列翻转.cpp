#include <bits/stdc++.h>
/*
遇到这种题目虽然要方法数，但是也不要先模拟，除非需要把所有的情况都列出来。从奇偶和0下手，然后分情况讨论，直接到结果
*/
/*
我们需要翻一些位置，错的必须翻，0的可以顺带翻，奇数和才能翻
如果是偶数和，那多翻一次就好了，
因为这是子序列，所以不需要考虑索引，而是考虑是否存在，一定是有一些特殊的元素存在的，同1，同0，好diff，坏diff
一些特殊元素的存在与否就能决定conduct次数
如果没有任何diff，但是坏diff还存在，就要想办法借用别的元素来判定了，不能这么草率的结束，认为conduct就是-1
*/
int main()
{
    std::vector<int> res;
    int cases = 0;
    std::cin >> cases;
    while (cases--)
    {
        std::vector<int> a;
        std::vector<int> b;
        int conduct = 0;
        std::vector<int> diffs;  // 如果a是1，b是0就丢进来，如果a的是0，转是没有代价的
        // //diff放入下标
        int diff = 0;
        int bad_diff = 0;
        int n;
        int same_one = 0;
        int same_zero = 0;
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            int num;
            std::cin >> num;
            a.push_back(num);
        }
        for (int i = 0; i < n; i++)
        {
            int num;
            std::cin >> num;
            b.push_back(num);
            if (b[i] != a[i])
            {
                if (a[i] == 1)
                {
                    diffs.push_back(i);
                    diff++;
                }
                else
                {
                    bad_diff++;
                }
            }
            else
            {
                if (a[i] == 1)
                {
                    same_one++;
                }
                else
                {
                    same_zero++;
                }
            }
        }
        if (diff % 2 != 0)  // 如果好的diff是奇数就直接换掉就好了，糟糕的diff可以顺带
        {
            conduct = 1;
        }
        else if (diff == 0 && bad_diff == 0)  // 和平
        {
            conduct = 0;
        }
        else if (diff % 2 == 0 && diff != 0)  // 如果diff是0的话就没有可用之兵
        {
            // 不管有没有糟糕diff就是先变一个，然后再变剩余的就好了
            conduct = 2;
        }
        else if (diff == 0 && bad_diff != 0)
        {
            // // 需要变化bad_diff但是没有可用兵
            // conduct = -1;这里太绝对了，虽然diff是0，但是依然可以有可用兵，同1和同0同时存在也可也用
            if (same_one == 0 || same_zero == 0)
            {
                conduct = -1;
            }
            else
            {
                conduct = 2;
            }
        }
        res.push_back(conduct);
    }
    for (int conduct : res)
    {
        std::cout << conduct << "\n";
    }
}