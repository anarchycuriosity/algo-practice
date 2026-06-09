#include <cmath>
#include <iostream>
// 有向图求每个点到达的最远序号
int n, m;
// 反向建图进行有效剪枝
// 为什么反向建图，因为这个题目的方向是固定的
// 也就是找序号最大的点（这很关键）
// 我们反向让大数统治小数，这样先被统治（染色）的数一定是被它能到达的最大的数所统治

// 这里出现了dfs的第三种形式，这里刚好也聊一下
// 这里的dfs函数没有使用参数传递结果，也没有用返回值
// 而是使用了一个max_reachable_point数组来储存想要的结果
// 出发点：dfs和记忆化天然挂钩
// 我们找1的最大点，比如1->2->4->6
// 我们标记1的最大点是6,但如果我们正向去找2,我们发现2的最大点其实在找1的最大点的时候已经顺便找到了
// 可是我们是正向建图,所以我们根本就不能记住2的最大点,但如果我们反向建图的话,2就能记住,因为方向已经固定的,我们只是去找一个方向
// 所以说这是这是定向建图

// 这里储存图的方式是邻接表，因为这是稀疏图，点和边的数量是一个量级（暂且这么简单判断吧）
#include <vector>
std::vector<std::vector<int>> reverse_g;  // 反向建图
std::vector<int> max_reachable_point;
// 经典的dfs搜索是盲目的，所以我们这里加上第二个参数max_val来确定它此行的目的
// 第一个参数当然是祖宗之法不可变，也就是当前节点确定状态，有了它我们才能去查邻接表
// 第二轮dfs，第二个参数要原封不动的传下去，因为是由第二个参数作为长官派遣的这个dfs
void dfs(int cur, int max_val)
{
    // 先染色，这是这个函数最主要的工作
    max_reachable_point[cur] = max_val;
    for (int neighbor : reverse_g[cur])
    {
        if (max_reachable_point[neighbor] == 0)
        {
            dfs(neighbor, max_val);
        }
    }
}
int main()
{
    std::cin >> n >> m;
    // n是点数，m是边数;
    reverse_g.resize(n + 1);
    max_reachable_point.resize(n + 1, 0);  // 初始化为0这种不会存在的数据
    for (int i = 1; i <= m; i++)           // 按边的数量读入然后建图
    {
        int from, to;
        std::cin >> from >> to;
        reverse_g[to].push_back(from);
    }
    for (int i = n; i >= 1; i--)
    {
        // 开始dfs遍历
        if (max_reachable_point[i] == 0)  // 这个判断容易漏加，但这个很关键
        {
            dfs(i, i);  // 长官先派遣自己去
        }
    }
    // max_reachable_point是正常顺序存
    // 反向存图主要是为了满足我们的需要，图依然是那个图，点点之间的关系是一定的，但是反向图可以让我们拿数据的效率更高
    for (int i = 1; i <= n; i++)
    {
        std::cout << max_reachable_point[i] << " ";
    }
}