#include <iostream>
using namespace std;
int a,b,c,ans;
void fast()
{
	int base = 2;;
	ans = a;
	while(base < b)
	{
		ans *= ans;
		ans %= c;
		b -= base;
		base *= 2;
	}
	for(int i = 1;i <= b - base;i++)
	{
		ans *= a;
	}
}
int main()
{
	cin >> a >> b >> c;
	fast();
	cout << ans;
}
