#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
// 拼错好多地方，这大概是答案不理想的原因之一，比如把[]塞到()里面
// 结束条件写错，应该是到n+1的时候退出
using namespace std;
// 上限其实不需要拿到10的六次方，也许可以每次滚动更新？
// 开两个dp数组
#define ll long long
const ll maxn = 2000;
const ll maxb = 1e6;
ll n, m;
ll w1[maxn], w2[maxn], v1[maxn], v2[maxn],
    // 但是最大重量挺大的，总和是10的六次方，一维数组开这么大ok吧
    dp1[maxb], dp2[maxb];
int main()
{
    // 因为每次都需要取最大值，所以初始化为-无穷
    memset(dp1, -0x3f, sizeof(dp1));
    memset(dp2, -0x3f, sizeof(dp2));
    dp1[0] = 0;
    dp2[0] = 0;
    // 只有首位取0，其他初始化为-无穷
    // 初始化这里说实话考场上记错了，用了递归来写
    // 关于01背包的初始化，理解的关键是一个合理的开始起点
    // 必须从一个正确的地方开始这个数据才有效，重量是有代价的
    // 如果是完全背包的顺序的话，遍历到的每个重量都是有效的
    // 但01背包不行
    // 冷知识，负无穷+整数还是负无穷，所以其实memset相当于ban了很多位置
    // 只有从0衍生出来的分支才有可能拿到价值
    cin >> n >> m;

    ll back1 = 0;
    ll back2 = 0;
    // ll i = 1;
    // ll j = 1;
    for (ll k = 1; k <= n; k++)
    {
        cin >> w1[k] >> v1[k]; // 这里输入错了，曾经写成v1
        back1 += w1[k];
        for (ll curb = back1; curb >= w1[k]; curb--)
        {
            dp1[curb] = max(dp1[curb], dp1[curb - w1[k]] + v1[k]);
        }
    }
    for (ll i = 1; i <= m; i++)
    {
        cin >> w2[i] >> v2[i];
        back2 += w2[i];
        for (ll curb = back2; curb >= w2[i]; curb--)
        {
            dp2[curb] = max(dp2[curb], dp2[curb - w2[i]] + v2[i]);
        }
    }

    // bool iover = false;
    // bool jover = false;
    // if (m == n)
    // {
    //     iover = true;
    //     jover = true;
    // }
    //  while (true)
    // {
    //     if (i == n + 1)
    //     {
    //         iover = true;
    //         break;
    //     }
    //     else if (j == m + 1)
    //     {
    //         jover = true;
    //         break;
    //     }
    //     back1 += w1[i];
    //     back2 += w2[j];
    //     for (ll curb = back1; curb >= w1[i]; curb--) // 因为没有重量限制，也许这里应该是到0?好吧不对,有种隐藏重量限制的感觉?大概可以理解，因为需要有curb - w的取舍
    //     {
    //         dp1[curb] = max(dp1[curb], dp1[curb - w1[i]] + v1[i]);
    //     }
    //     for (ll curb = back2; curb >= w2[j]; curb--)
    //     {
    //         dp2[curb] = max(dp2[curb], dp2[curb - w2[j]] + v2[j]);
    //     }
    //     i++;
    //     j++;
    // }
    // if (!(iover && jover))
    // {
    //     if (iover == true && jover == false)
    //     {
    //         while (true)
    //         {
    //             if (j == m + 1)
    //             {
    //                 jover = true;
    //                 break;
    //             }
    //             back2 += w2[j];
    //             for (ll curb = back2; curb >= w2[j]; curb--)
    //             {
    //                 dp2[curb] = max(dp2[curb], dp2[curb - w2[j]] + v2[j]);
    //             }
    //             j++;
    //         }
    //     }
    //     else if (jover == true && iover == false)
    //     {
    //         while (true)
    //         {
    //             if (i == n + 1)
    //             {
    //                 iover = true;
    //                 break;
    //             }
    //             back1 += w1[i];
    //             for (ll curb = back1; curb >= w1[i]; curb--)
    //             {
    //                 dp1[curb] = max(dp1[curb], dp1[curb - w1[i]] + v1[i]);
    //             }
    //             i++;
    //         }
    //     }
    // }
    ll ans = 0;
    for (ll curb = 0; curb <= back1; curb++)
    {
        ans = max(ans, dp1[curb] + dp2[curb]); // 天啊，如果数据无效就是-无穷
    }
    cout << ans;
}