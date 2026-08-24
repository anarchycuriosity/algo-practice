/*
这个和找点dp似乎又不太一样的了,因为你不再能仅仅根据上一个点的长度取min了,还多了一个走完线段的支线任务.
我一开始想是否应该去探知下一层然后提前在这层走到一端这样就不用走重复的路程但我意识到这不可能因为影响是会扩散的,所以只能根据上一次走过的结果dp.
A:假如你要最终停在这层的左端,最短距离肯定是
∣x−Ri​∣+(Ri​−Li​)
为什么只有“停左边 / 停右边”两个状态？
你可能会问：
我走完线段之后，为什么非得停在端点？
我不能走完以后再走到某个中间位置，方便下一行吗？
现在回头想想这个想法其实很蠢
所以所有“为了下一行提前横着走”的动作，都可以延迟到下一行再做,这是一样的

这里的元素是具体的长度而不是方法
空方法是1,但是空的长度不会是1
所以我们要初始化一个具体的东西,,然后从起点往后延迟一个迭代
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    ll n;
    ll L[20005], R[20005];  // 这里可能出现给的不够多的问题,题目说的范围是2e4
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> L[i] >> R[i];
    }
    ll len = R[1] - L[1];
    ll dpL = 0;
    ll dpR = 0;
    dpL = abs((ll)1 - R[1]) + len;
    dpR = abs((ll)1 - L[1]) + len;
    for (int i = 2; i <= n; i++)  // 第n行也有支线任务
    {
        len = R[i] - L[i];
        ll newL = min(dpL + abs(R[i] - L[i - 1]) + len + 1, dpR + abs(R[i] - R[i - 1]) + len + 1);
        ll newR = min(dpL + abs(L[i] - L[i - 1]) + len + 1, dpR + abs(L[i] - R[i - 1]) + len + 1);
        dpL = newL;
        dpR = newR;
    }
    ll ans = min(dpL + abs(L[n] - n), dpR + abs(R[n] - n));
    cout << ans;
}
