// 为什么这题我们会考虑用桶排序呢，因为这题分数的范围是规定的
// 你可以把桶想象成有很多标签的箱子，比如0-600分就有600个箱子，你遇到一个对应分数你就投一个硬币到对应箱子
// 整个过程完全不会比较，因为桶排序的关键是我们完全不需要马上把数据放在最准确的地方
// 我们这题只是为了拿符合要求的某个特定的数，所以我们要使用方便的数据结构
// 这和堆的思维是一致的
#include <iostream>
int n, w;  // n是选手总数，w是获奖率,w%
#include <cmath>
#include <vector>
std::vector<int> buck;
int main()
{
    std::cin >> n >> w;
    // 不要写成buck.resize(n+1,0);
    buck.resize(601, 0);
    std::vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        int score;
        std::cin >> score;
        buck[score]++;
        int tar = std::max(1, i * w / 100);  // 求你好好读题
        int cur_ind = 600;                   // 从上往下数，别赋值为0搞反了
        while (tar > 0)
        {
            // if (cur_ind == 0)
            // {
            //     break;
            // }
            if (buck[cur_ind] == 0)
            {
                // continue之后要记得自减啊，不然下次进来它还是这样，死循环
                cur_ind--;
                continue;
            }
            // 不要搞反了，执行顺序很重要，先处理cur节点的数据，再对cur迭代
            tar -= buck[cur_ind];
            // 在这里截断一下，不然分数线会多减掉
            if (tar <= 0)
            {
                break;
            }
            cur_ind--;

            // 不能在这里push，while循环找完之后再push
        }
        ans.push_back(cur_ind);
    }
    // for (int i = 0; i < ans.size(); i++)
    // {
    //     std::cout << ans[i] << " ";
    // }
    for (int line : ans)
    {
        std::cout << line << " ";
    }
}