#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
ll n, M, T;
const ll maxn = 1001;
ll mco[maxn], tco[maxn];
ll mem[maxn][maxn];
int main()
{
    cin >> n >> M >> T;
    for (ll i = 1; i <= n; i++)
    {
        cin >> mco[i] >> tco[i];
    }
    for (ll k = 1; k <= n; k++)
    {
        for (ll mleft = M; mleft >= mco[k]; mleft--)
        {
            for (ll tleft = T; tleft >= tco[k]; tleft--)
            {
                mem[mleft][tleft] = max(mem[mleft][tleft], mem[mleft - mco[k]][tleft - tco[k]] + 1);
            }
        }
    }
    cout << mem[M][T];
    return 0;
}
