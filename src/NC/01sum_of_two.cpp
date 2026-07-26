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
        std::vector<int> res;
        struct num
        {
            int val;
            int ind;
        };
        std::vector<num> vec;
        for (int i = 0; i < numbers.size(); i++)
        {
            int val = numbers[i];
            int ind = i;
            vec.push_back({val, ind});
        }
        std::sort(vec.begin(), vec.end(), [](num& a, num& b) { return a.val < b.val; });
        for (int i = 0; i < vec.size() - 2; i++)
        {
            int a = vec[i].val;
            int ind_a = vec[i].ind;
            int left = i + 1;
            int right = vec.size() - 1;
            int mid;
            while (left < right)
            {
                mid = left + (right - left) / 2;
                int b = vec[mid].val;
                if (a + b < target)
                {
                    left = mid;
                }
                else if (a + b > target)
                {
                    right = mid;
                }
                else
                {
                    res.push_back(ind_a + 1);
                    res.push_back(mid + 1);
                    return res;
                }
            }
        }
        return res;
    }
};
int main()
{
    std::vector<int> test({20, 70, 110, 150});
    int target = 90;
    Solution sol;
    std::vector<int> res = sol.twoSum(test, target);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " ";
    }
}