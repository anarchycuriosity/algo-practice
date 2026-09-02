/*
每个点只有一条出边 ⇒ 一直走一定最终进入环。
这题就是找最短环
入度为 0 的点一定不在环里
不妨删掉没有环的元素,删掉之后会发生连锁反应
这其实就是你以后会经常见到的：
拓扑排序的删点思想。

删除不一定能要真的删除,另外设置一个数组记录删除位置true,也就是软删除

待处理点是在算法运行过程中动态产生的,所以queue比for循环更好处理
甚至这道题实际上用 stack 也能做：

因为我们并不在乎这些入度 0 的点谁先删。

queue 的真正意义不是“先进先出有什么神奇性质”，而是：

保存所有已经发现，但还没有处理的

这和 BFS 里的 queue 其实是同一个非常重要的思想。
而且这是出度为1,一个节点入环之后就不会再出去了,所以不会出现电话线那样的结构,所以用此处源码的逻辑是可以删干净的
每个连通块恰好只有一个环
        ​

*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> to(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> to[i];
        indegree[to[i]]++;
    }
    // 现在开始删,想象从外皮剥洋葱,现在把外皮存进去
    // 这里可能有多个洋葱,每个洋葱只有一个外皮,然后我们存多个外皮进去
    queue<int> to_remove;
    vector<bool> removed(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            to_remove.push(i);
        }
    }
    while (!to_remove.empty())
    {
        // u -> v
        int u = to_remove.front();
        to_remove.pop();
        removed[u] = true;
        int v = to[u];
        indegree[v]--;
        if (indegree[v] == 0)
        {
            to_remove.push(v);
        }
    }
    const int INF = 1e9;
    int ans = INF;
    // well,最好加个vis,不然会遍历太多
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        if (removed[i] == true || vis[i] == true)
        {
            continue;
        }
        int cnt = 0;
        int cur = i;
        // while (to[cur] != i)
        while (vis[cur] == false)
        {
            vis[cur] = true;
            cur = to[cur];
            cnt++;
        }
        ans = min(ans, cnt);
    }
    cout << ans;
}
