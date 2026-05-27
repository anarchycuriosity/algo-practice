// 假设你有一个专门存储二进制拆分后物品的数组和计数器
// int current_idx = 0;
#include <iostream>
using namespace std;
#define ll long long
struct saku
{
	ll w;
	ll v;
	ll times;
};
struct item
{
	ll v;
	ll w;	
};
//vector<item> items;
//用这个会超时
//好吧其实不用也超时 

const ll maxn = 1000031;
ll h1,h2,m1,m2;
ll back;
saku sakus[maxn];
item items[maxn]; 
ll n;
ll index = 1;

ll mem[maxn];
char ch;
int main()
{
//	items.push_back({});
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
//	scanf("%lld:%lld %lld:%lld",&h1,&m1,&h2,&m2);//记得取地址 不要混用 
//	scanf("%d:%d",&h2,&m2);
	cin >> h1 >> ch >> m1 >> h2 >> ch >> m2;
	back = h2 * 60 + m2 - h1 * 60 - m1;
//	cout << back << "\n";
	cin >> n;
	for (ll i = 1; i <= n; i++)
{
	cin >> sakus[i].w >>sakus[i].v >> sakus[i].times;
    if (sakus[i].times == 0)
    {

        // 如果是无限物品，直接进行完全背包逻辑
        // 建议：不要塞进 items 数组，在这一步单独处理或者换个方式记录
        // 为了方便，你可以加一个标记数组，或者在这里直接 DP
        for (ll j = sakus[i].w; j <= back; j++)
        {
            mem[j] = std::max(mem[j], mem[j - sakus[i].w] + sakus[i].v);
        }
        continue; // 跳过后续的二进制拆分
    }

    // 只有有限物品才进行二进制拆分
    ll count = sakus[i].times;
    ll v = sakus[i].v;
    ll w = sakus[i].w;

    for (ll base = 1; base <= count; base <<= 1)
    {
        items[index++] = {v * base, w * base};
        count -= base;
    }
    // 只有当还有剩余时，才把剩余的部分补上
    if (count > 0)
    {
        items[index++] = {v * count, w * count};
    }
}
//	for(ll i = 1;i <= n;i++)
//	{
//		if(sakus[i].times == 0)
//		{
//			for(ll left = sakus[i].w ;left <= back;left++)
//			{
//				mem[left] = max(mem[left],mem[left - sakus[i].w ]+ sakus[i].v);
//			}
//		}
//		else
//		{

			//把有限背包问题变成01背包问题 
			//优化了第一次遍历决定拿几根的部分for(ll time = 1;time <= sakus[i].times ;time++) 


			
			
			
						//我们需要对拿几次做额外的遍历，对1到n次都做一个01背包
//			for(ll time = 1;time <= sakus[i].times ;time++)
//			{
//				
//				for(ll left = back;left >= time * sakus[i].w ;left--)//time *来保证前面的部分不要被遍历到，不然就超时WA 
//				{
//					mem[left] = max(mem[left],mem[left - sakus[i].w] + sakus[i].v );
//				}
//			 } 
//		}
//	}
	for(int j = 1;j <= index;j++)
	{
		for(ll left = back;left >= items[j].w;left--)
		{
			mem[left] = max(mem[left],mem[left - items[j].w] + items[j].v);
		}
	}
	cout << mem[back];
	
}

