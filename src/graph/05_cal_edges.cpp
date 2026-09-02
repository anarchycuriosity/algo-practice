#include <bits/stdc++.h>
using namespace std;
/*
ans[u] = ans[v] + 1;

这个公式成立有一个隐藏条件：

从 v 出发以后，永远不会再次访问 u。
*/
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
    queue<int> to_remove;

    vector<bool> removed(n + 1, false);
    vector<int> order;  // 保存删除的节点,当然删除动作依然要依靠queue
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            to_remove.push(i);
        }
    }
    while (!to_remove.empty())
    {
        int u = to_remove.front();
        to_remove.pop();
        order.push_back(u);
        removed[u] = true;
        int v = to[u];
        indegree[v]--;
        if (indegree[v] == 0)
        {
            to_remove.push(v);
        }
    }

    vector<int> ans(n + 1, 0);
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        // if (vis[i] || removed[i])//因为都要考虑,环以外的东西并非真的删除
        if (vis[i])
        {
            continue;
        }
        // 因为环上每个都要标记,所以使用do while
        if (indegree[i] > 0)
        {
            int cur = i;
            int len = 0;
            do
            {
                vis[cur] = true;
                len++;
                cur = to[cur];
            } while (cur != i);
            // } while (to[cur] != i);//这样会提前一步停下
            cur = i;  // 这个是否有点多余
            do
            {
                ans[cur] = len;
                cur = to[cur];
            } while (cur != i);
        }
    }
    for (int i = order.size() - 1; i >= 0; i--)
    {
        int u = order[i];
        int v = to[u];
        ans[u] = ans[v] + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << "\n";
    }
}