#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, b;
#define maxn 13010
int tcost[maxn], mget[maxn];
int mem[maxn];
int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> tcost[i] >> mget[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int bleft = b; bleft >= tcost[i]; bleft--)
        {
            mem[bleft] = max(mem[bleft], mem[bleft - tcost[i]] + mget[i]);
        }
    }
    cout << mem[b];
}
