#include <iostream>
#define ll long long
using namespace std;
ll a,b,c,ans,base;
void fast()
{
	a %= c;
	ans = 1;
	base = a;
	while(b > 0)
	{
		if(b & 1)
		{
			ans *= base;
			ans %= c;
		}
		base *= base;
		base %= c;
		b >>=1;
		
	}
}
int main()
{
	cin >> a >> b >> c;
	ll bb = b;
	fast();
	cout << a << "^" << bb << " mod " << c << "=" << ans;
}
