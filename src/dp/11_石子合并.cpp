#include <iostream>
#include <string.h>
#include <algorithm>
#define ll long long
using namespace std;
const ll maxn = 1001;
ll n;
ll w[maxn];
ll sum[maxn];
ll mem[maxn][maxn];

int main()
{
	memset(mem,0x3f,sizeof(mem));
	cin >> n;
	for(ll i = 1;i <= n;i++)
	{
		cin >> w[i];
		sum[i] = sum[i-1]+w[i];
		mem[i][i] = 0;//从自己到自己的代价为0 
	}	

	//如果我们想要得到整个的最小值，就要得到部分融合的最小值 
	//长度
	//起点
	//记录终点，然后找中间点
	for(ll len = 2;len <= n;len++)//这里的长度和你想象的长度不太一致，而是包含了几个元素的意思
	{//最关键的是理解当len = 2的时候，k只能取i这一种可能，12，23，34都是正常的区间和
	//然后是len = 3的时候，拿i = 1来说，k有两种可能，在13中11+23或者12+33
	//对于这个三石头堆而言，就是先合并左边两个还是先合并右边两个的问题，前提是剩下的这一个（如果是4就是剩下这两个)已经是最优解，这里是0 
	//对于n个石头堆而言，分成左右两堆，再分一次，每次使用合并的石堆都是最优解，就看k插在哪 
		for(ll i = 1;i <= n - len +1;i++)
		{
			ll j = i + len - 1;
			for(ll k = i;k < j;k++)//你想象一下把k横中间看看两边有没有元素，如果没有元素就错了，比如
			//当k是j的时候，左区间是ij，右区间是j+1开始，发现是空的
			{
				mem[i][j] = min(mem[i][j],mem[i][k]+mem[k+1][j]+ sum[j] - sum[i-1]);
			 } 
		}
	 } 
	 cout << mem[1][n];
	
	 
	
} 
