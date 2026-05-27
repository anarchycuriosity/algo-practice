#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T,m;
const ll maxn = 1e7+5;
ll w[maxn],v[maxn];
ll mem[maxn];
int main()
{
	cin >> T >> m;
	for(ll i = 1;i <= m;i++)
	{
		cin >> w[i] >> v[i];
	}
	for(ll i = 1; i <= m;i++)
	{
		for(ll left = w[i];left <= T;left++)
		{
			mem[left] = max(mem[left],mem[left - w[i]] + v[i]);
		}
	}
	cout << mem[T];
}
