#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int n;
	//注意这里其实0就是下一集了
	//dp必须从头开始，所以也不会走到n而是n -1 
	cin >> n;
	int a;
	ll sol[1001];//不开ll见祖宗 
	sol[0] = 1;
	sol[1] = 2;
	sol[2] = 4;
	for(int i = 3;i < n;i++)
	{
		sol[i] += sol[i-1] + sol[i -2] + sol[i - 3];
	}
	cout << sol[n-1];
	
}
