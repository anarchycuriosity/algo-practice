#include <bits/stdc++.h>
using namespace std;
#define ll long long
// 这题不开ll见祖宗
ll ans = 0;
vector<int> nums;
vector<int> temp;
void merge_sort(int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    // 这两个merge_sort结束后已经把这个数组分到不能再分了,最小单位天然有序
    // 把数组的两块合并,l开头的一边和mid开头的一边
    int i = l;
    int j = mid + 1;
    int k = l;  // l和j是双指针,k是temp数组上的指针
    while (i <= mid && j <= r)
    {
        if (nums[i] <= nums[j])
        {
            temp[k++] = nums[i++];
        }
        else
        {
            temp[k++] = nums[j++];
            ans += mid - i + 1;
        }
    }

    while (i <= mid)
    {
        temp[k++] = nums[i++];
    }
    while (j <= r)
    {
        temp[k++] = nums[j++];
    }
    for (int p = l; p <= r; p++)
    {
        nums[p] = temp[p];
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    // 不要忘了resize
    temp.resize(n);
    merge_sort(0, n - 1);
    cout << ans;
}