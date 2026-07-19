#include <iostream>
#include <vector>

// 2 * 10e9或者2^31的时候需要开ll
#define ll long long
int n;
ll p;
int main()
{
    std::cin >> n >> p;
    std::vector<int> invs(n + 1, 1);
    std::vector<int> ans;
    // i是1到n的迭代器
    // 在i的实际迭代的过程中，k和r只需要一次计算即可算出，也就是整除和取余
    ans.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        int k = p / i;
        int r = p % i;
        invs[i] = ((p - k) * invs[r]) % p;
        ans.push_back(invs[i]);
    }
    for (int ind = 0; ind < ans.size(); ind++)
    {
        std::cout << ans[ind] << "\n";
    }
}