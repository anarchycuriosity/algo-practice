#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> to(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> to[i];
        indegree[to[i]]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    // 保存所有被删除的环外节点
    vector<int> order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        order.push_back(u);

        int v = to[u];
        indegree[v]--;

        if (indegree[v] == 0)
        {
            q.push(v);
        }
    }

    vector<int> ans(n + 1, 0);
    vector<bool> vis(n + 1, false);

    // 此时 indegree[i] > 0 的点全部属于环
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] > 0 && !vis[i])
        {
            // 先算这个环的长度
            int len = 0;
            int cur = i;

            do
            {
                vis[cur] = true;
                len++;
                cur = to[cur];
            } while (cur != i);

            // 环上的所有点答案都是环长
            cur = i;

            do
            {
                ans[cur] = len;
                cur = to[cur];
            } while (cur != i);
        }
    }

    // 倒着处理被删掉的节点
    for (int i = (int)order.size() - 1; i >= 0; i--)
    {
        int u = order[i];
        ans[u] = ans[to[u]] + 1;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << '\n';
    }

    return 0;
}