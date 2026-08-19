#include <bits/stdc++.h>

/*
看到“所有东西都出现偶数次，只有一个出现奇数次”时，要想到 XOR。
我们希望消掉所有成对出现的数字,这时候就要考虑异或运算
而且这题的n有1e7,这就意味着无法开大数组

&   → 筛选 / 保留
|   → 打开 / 设置
^   → 翻转 / 消除

也许你一开始会疑惑如果两个数比对的时候不一样那不是全乱了吗,但是因为异或运算满足交换律和结合律
同时0 ^ a == a

*/
int main()
{
    int total = 0;
    int tmp = 0;
    int n;
    std::cin >> n;
    while (n--)
    {
        std::cin >> tmp;
        total ^= tmp;
    }
    std::cout << total;
}