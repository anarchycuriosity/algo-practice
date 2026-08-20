#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Arr
{
    ll x, y;
};
ll get_small_key(Arr& arr) { return min(arr.x, arr.y); }
ll get_big_key(Arr& arr) { return max(arr.x, arr.y); }
bool comp(Arr& arr1, Arr& arr2)  // 需要交换就返回true
// 好吧准确来说应该是谁应该在前面,默认arr1在前面
{
    // 不交换
    // ll cnt1 = (arr1.x > arr2.x) + (arr1.x > arr2.y) + (arr1.y > arr2.x) + (arr1.y > arr2.y);
    // ll cnt2 = (arr2.x > arr1.x) + (arr2.x > arr1.y) + (arr2.y > arr1.x) + (arr2.y > arr1.y);
    // return (cnt1 > cnt2);
    if (get_small_key(arr1) < get_small_key(arr2))
    {
        return true;
    }
    else if (get_small_key(arr1) == get_small_key(arr2))
    {
        if (get_big_key(arr1) < get_big_key(arr2))
        {
            return true;
        }
        return false;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<ll>> ans;
    ll t;
    cin >> t;
    ll tt = t;

    while (tt--)
    {
        ll n;
        cin >> n;
        ll nn = n;
        vector<Arr> arrs;
        while (nn--)
        {
            ll x, y;
            cin >> x >> y;
            // Arr arr;
            // arr.x = x;
            // arr.y = y;
            // arrs.push_back(arr);
            arrs.push_back({x, y});
        }
        sort(arrs.begin(), arrs.end(), comp);
        vector<ll> tmp;
        for (ll i = 0; i < arrs.size(); i++)
        {
            tmp.push_back(arrs[i].x);
            tmp.push_back(arrs[i].y);
        }
        ans.push_back(tmp);
    }
    for (ll i = 0; i < t; i++)
    {
        for (ll j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}