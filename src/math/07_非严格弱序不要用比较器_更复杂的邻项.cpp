#include <bits/stdc++.h>
using namespace std;
struct Arr
{
    int x, y;
};
bool comp(Arr& arr1, Arr& arr2)  // 需要交换就返回true
// 好吧准确来说应该是谁应该在前面,默认arr1在前面
{
    // 不交换
    // int cnt1 = (arr1.x > arr2.x) + (arr1.x > arr2.y) + (arr1.y > arr2.x) + (arr1.y > arr2.y);
    // int cnt2 = (arr2.x > arr1.x) + (arr2.x > arr1.y) + (arr2.y > arr1.x) + (arr2.y > arr1.y);
    // return (cnt1 > cnt2);
    return max(arr1.x, arr1.y) > max(arr2.x, arr2.y);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> ans;
    int t;
    cin >> t;
    int tt = t;

    while (tt--)
    {
        int n;
        cin >> n;
        int nn = n;
        vector<Arr> arrs;
        while (nn--)
        {
            int x, y;
            cin >> x >> y;
            // Arr arr;
            // arr.x = x;
            // arr.y = y;
            // arrs.push_back(arr);
            arrs.push_back({x, y});
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j > 0; j--)
            {
                if (comp(arrs[j - 1], arrs[j]))
                {
                    swap(arrs[j - 1], arrs[j]);
                }
            }
        }
        vector<int> tmp;
        for (int i = 0; i < arrs.size(); i++)
        {
            tmp.push_back(arrs[i].x);
            tmp.push_back(arrs[i].y);
        }
        ans.push_back(tmp);
    }
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}