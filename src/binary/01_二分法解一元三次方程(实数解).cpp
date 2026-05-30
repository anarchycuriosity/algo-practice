// 有个疑惑点也许是误差>0或者<0应该左转或者右转
// 也许这不是很重要，只要转就好了
// 转齐次方程然后算，而且只要找一个解，判断解的依据就是找到小于某个误差的函数返回值
// 在此基础上继续二分
// 判断0解和其他解的逻辑完全不一样，所以要单独写一个逻辑判断0解【需要注意】
// 找解的基础依然是for里面int i循环，因为两个解之间的误差差不多是1
// 有点像移动窗口法？在这个窗口里面二分
// 二分在这里的作用就是控制精度
#include <algorithm>  //不要直接输出，答案要求需要先排序
#include <cmath>
#include <iomanip>
#include <vector>
double a, b, c, d;
int count = 0;  // 控制解的数量，毕竟三个解
double cal(double x) { return (a * x * x * x + b * x * x + c * x + d); }
#include <iostream>
int main()
{
    std::cin >> a >> b >> c >> d;
    double y1, y2, l, r, m;  // l和r是窗口的边界,两个y是齐次方程的左值
    std::cout << std::fixed;
    std::cout << std::setprecision(2);  // 参数设置输出小数点后两位，忘记了（笑哭）
    std::vector<double> ans;
    for (int i = -100; i <= 100; i++)
    {
        l = i;
        r = i + 1;
        y1 = cal(l);
        y2 = cal(r);
        if (!y1)
        {
            ans.push_back(l);
            // std::cout << " " << l;
            count++;
        }
        if (count == 3)
        {
            break;
        }
        // 二分的依据是零点定理
        if (y1 * y2 < 0)
        {
            while (r - l >= 0.001)
            {
                m = (l + r) / 2;
                if (cal(l) <= 0)  // 我不太确定这里是否要取等
                {
                    l = m;
                }
                else
                {
                    r = m;
                }
            }
            // 控制完精度就输出
            count++;
            ans.push_back(m);
            // std::cout << m << " ";
        }
    }
    std::sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
    {
        std::cout << ans[i] << " ";
    }
}