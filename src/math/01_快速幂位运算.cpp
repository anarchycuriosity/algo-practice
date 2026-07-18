#include <iostream>
#define ll long long
using namespace std;
ll a, b, c, ans, base;
void fast()
{
    a %= c;  // 这里涉及一个同类余的数学知识，提前取一次余并不会导致结果错误
             // 但是因为答案有打印的要求，所以要留个备份，对a或者b进行操作，但是aa和bb用来打印
    ans = 1;
    base = a;
    // ans默认值为0也许就判断了b为0这个边界
    while (b > 0)
    {
        if (b & 1)
        {
            ans *= base;
            ans %= c;
        }
        base *= base;
        base %= c;
        b >>= 1;
    }
}
int main()
{
    cin >> a >> b >> c;
    ll aa = a;
    ll bb = b;
    fast();
    cout << aa << "^" << bb << " mod " << c << "=" << ans;
}
