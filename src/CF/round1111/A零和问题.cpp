// 这题只需要判断yes还是no，所以操作空间很多，代价不重要
// 所以我们只需要盯着初始时候的变化量和不变量，而不能去模拟
// 竞赛题里的操作，往往不是让你去执行，而是让你去研究它们会保留什么。
#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    std::vector<std::string> judges;
    while (t--)
    {
        int count;
        std::cin >> count;
        // if (count % 2 != 0)
        // {
        //     judges.push_back("NO");
        //     continue;
        // }别写在这里，不然输入会被卡死
        std::vector<int> nums;
        int cnt_p = 0;
        int cnt_m = 0;
        int n = count;  // 把count保留下来方便后面判断，不然--它变化了就不能判断了
        while (n--)
        {
            int num;
            std::cin >> num;
            if (num > 0)
            {
                cnt_p++;
            }
            else
            {
                cnt_m++;
            }
            nums.push_back(num);
        }
        if (count % 2 != 0)
        {
            judges.push_back("NO");
            continue;
        }
        if (cnt_p % 2 == (count / 2) % 2)
        {
            judges.push_back("YES");
        }
        else
        {
            judges.push_back("NO");
        }
    }
    for (size_t i = 0; i < judges.size(); i++)
    {
        std::cout << judges[i] << "\n";
    }
}