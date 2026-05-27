#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, b;
#define maxn 13010
int tcost[maxn], mget[maxn];
int mem[maxn];  // 锟铰憋拷锟斤拷锟斤拷锟斤拷
int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> tcost[i] >> mget[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int bleft = b; bleft >= tcost[i]; bleft--)  // 锟斤拷锟斤拷证锟斤拷锟斤拷锟矫碉拷锟斤拷锟斤拷锟斤拷一锟街的撅拷值
        {                                                // mem[bleft -
           // tcost[i]]魔锟斤拷锟斤拷锟斤拷锟斤拷锟斤，锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟皆感撅拷锟斤拷锟斤拷锟角碉拷锟斤拷模锟斤拷锟斤拷堑菁锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷也锟斤拷锟脚递硷拷锟斤拷每锟斤拷位锟矫碉拷值锟酵诧拷锟斤拷锟节憋拷锟街革拷锟铰ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷一锟街的撅拷值
            mem[bleft] = max(mem[bleft], mem[bleft - tcost[i]] + mget[i]);
        }
    }
    cout << mem[b];
}
