#include <bits/stdc++.h>
using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    double avg = 0;
    vector<int> nums;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    sort(nums.begin(), nums.end(), [](int a, int b) { return a < b; });
    vector<int> bad_nums;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        bad_nums.push_back(nums[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (avg > nums[i])
        {
            avg = (avg * i + 0) / (i + 1);
        }
        else
        {
            avg = (avg * i + m) / (i + 1);
        }
    }
    double bad_avg = 0;
    for (int i = 0; i < n; i++)
    {
        if (bad_avg > bad_nums[i])
        {
            bad_avg = (bad_avg * i + 0) / (i + 1);
        }
        else
        {
            bad_avg = (bad_avg * i + m) / (i + 1);
        }
    }
    cout << fixed << setprecision(2) << avg << " " << bad_avg;
}