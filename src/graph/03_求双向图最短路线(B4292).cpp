#include <iostream>
#include <vector>
int n, m;
std::vector<std::vector<int>> g;
// std::vector<bool> visit;
#include <queue>
// 因为这个不需要扫完全部节点，所以我们考虑用参数拿到数据？
// 还是用数组记录吧，然后bfs也不用写了因为遇到了就直接终结就好了

int main()
{
    std::cin >> n >> m;
    g.resize(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int from, to;
        std::cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
    }
    std::queue<int> q;
    std::vector<int> ans;
    ans.resize(n + 1, -1);  // 初始化为负数，-1的意义比较明显
    // 从终点的0开扫，这样第一层扫到的就是1，第二层扫到的就是2
    ans[n] = 0;
    q.push(n);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int neighbor : g[cur])
        {
            if (ans[neighbor] == -1)
            {
                q.push(neighbor);
                ans[neighbor] = ans[cur] + 1;
            }
        }
    }
    for (int i = 1; i <= n - 1; i++)
    {
        std::cout << ans[i] << " ";
    }
}