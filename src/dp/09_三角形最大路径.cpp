#include <bits/stdc++.h>
using namespace std;
	int r;//行数
#define ll long long 
int tow[1001][1001],dp[1001][1001];

//我们递归的目的是为了拿到记忆数组，如果记忆数组已经拿到了就应该布置return任务回来 
//我们要拿到递归的结果，返回值如果是void就拿不到了 
int solve(int i,int j)
{
	if(i == r)
	{
		return tow[i][j];
	}

	if(dp[i][j]!=-1)
	{
		return dp[i][j];//如果已经记录过数据了就直接返回 
	}
//	else这里不能用这个else，因为记录结果应该是任何时候都要更新的，如果用了else就只有在没有任何结果的时候才会更新数据 
//	{
	int left = solve(i+1,j);
	int right = solve(i+1,j+1);
		dp[i][j] = tow[i][j]+ max(left,right);
//	}
	return dp[i][j];
}

int main()
{

	cin >> r;
	for(int i = 1;i <= r;i++)
	{
		for(int j = 1;j <= i;j++)
		{
			cin >> tow[i][j];
			dp[i][j] = -1;	
		}	
	} 
	cout << solve(1,1);
	return 0;
}

