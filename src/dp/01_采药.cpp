#include <bits/stdc++.h>
using namespace std;
int tcost[1001],mget[1001],mem[1001][1001];
#define INF -1000001

//记忆组的下标往往应该是怎么规定的？也许是有几个维度的判断元素就开几维数组
//这里二维记忆数组的第一层是递归层数，或者说是第几颗草药，第二层是时间，储存的是价格 
//比如这里有价格和时间两个因素，在三角形最长路径那题有i和j来判断元素位置
	int n;
	//必须要用dfs拿到选择的结果，所以返回值应该是int而不是void 
	//与void类型的dfs不同，void需要get来储存结果，如果返回值是int其实就不需要了 
int dfs(int i,int tleft)
{
	//这样写其实不对，因为最后一颗草也是要找的，应该要找到n + 1的草然后标记为0已读让它不影响计算 
//	if(i == n)//找到最后一棵草就返回mem 
//	{
//		return mem[i][tleft];//不要随便return 
//	}
//	if(tleft < 0)在下文使用防止进入递归的替代此块 
//	{
//		return mem[i][tleft];
//	}

	//我们其实相当于从后往前拿，但是我们顺着递归往后找
	//第一次找到i的时候其实我们不会拿这颗草，我们会等递归的函数返回来 

	if(i == n + 1)
	{
		return mem[i][tleft] = 0;
	}
	
	if(mem[i][tleft] != -1)
	{
		return mem[i][tleft];
	}

//如果剩下的时间不够拿这颗草就不拿了
//这么说不太对，应该是如果还有时间才有机会继续递归下去，否则不行 
	int take = INF,not_take = INF;
	if(tleft >= tcost[i])
	{
		take = dfs(i+1,tleft - tcost[i]) + mget[i];
	} 
	not_take = dfs(i +1 ,tleft);
//	return max(take,not_take);不要忘了保存记忆数组，否则没有意义了
	return mem[i][tleft] = max(take,not_take); 

	
	
	
}
int main()
{
	int T;
	cin >> T;

	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> tcost[i] >> mget[i];
	}
	memset(mem,-1,sizeof(mem));
	cout << dfs(1,T);
}
