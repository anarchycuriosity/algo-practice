#include <bits/stdc++.h>
using namespace std;
class Solution
{
   public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param numbers int整型vector
     * @param target int整型
     * @return int整型vector
     */
    vector<int> twoSum(vector<int>& numbers, int target)
    {
#define ll long long
        // write code here
        std::unordered_map<int, std::vector<int>> map;  // 键是数值，值是对应的ind
        std::vector<int> res;
        for (int i = 0; i < numbers.size(); i++)
        {
            map[numbers[i]].push_back(i);
        }
        for (int i = 0; i < numbers.size(); i++)
        {
            int a = numbers[i];
            int tar = target - a;
            if (tar == a)
            {
                if (map.find(tar) != map.end() && map[tar].size() != 1)
                {
                    res.push_back(map[a][0] + 1);
                    res.push_back(map[tar][1] + 1);
                    return res;
                    break;
                }
            }
            else
            {
                if (map.find(tar) != map.end())
                {
                    res.push_back(map[a][0] + 1);
                    res.push_back(map[tar][0] + 1);
                    return res;  // 这个很容易漏
                }
            }
        }
        return res;
    }
};
int main()
{
    std::vector<int> test({3, 2, 4, 0});
    int target = 6;
    Solution sol;
    std::vector<int> res = sol.twoSum(test, target);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " ";
    }
}