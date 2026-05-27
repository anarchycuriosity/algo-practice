#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct saku
{
    ll w;
    ll v;
    ll times;
};
const ll maxn = 10031;
ll h1, h2, m1, m2;
ll back;
saku sakus[maxn];
ll n;

ll mem[maxn];
int main()
{
    scanf("%lld:%lld %lld:%lld", &h1, &m1, &h2, &m2);  // 记得取地址
    //	scanf("%d:%d",&h2,&m2);
    back = h2 * 60 + m2 - h1 * 60 - m1;
    cout << back << "\n";
    cin >> n;
    for (ll i = 1; i <= n; i++)
    {
        cin >> sakus[i].w >> sakus[i].v >> sakus[i].times;
    }
    for (ll i = 1; i <= n; i++)
    {
        if (sakus[i].times == 0)
        {
            for (ll left = sakus[i].w; left <= back; left++)
            {
                mem[left] = max(mem[left], mem[left - sakus[i].w] + sakus[i].v);
            }
        }
        else
        {
            // 我们需要对拿几次做额外的遍历，对1到n次都做一个01背包
            for (ll time = 1; time <= sakus[i].times; time++)
            {
                for (ll left = back; left >= time * sakus[i].w;
                     left--)  // time *来保证前面的部分不要被遍历到，不然就超时WA
                {
                    mem[left] = max(mem[left], mem[left - sakus[i].w] + sakus[i].v);
                }
            }
        }
    }
    cout << mem[back];
}
