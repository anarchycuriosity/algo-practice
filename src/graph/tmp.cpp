#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
    int w;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
    }

    const long long INF = (1LL << 60);

    vector<long long> dist(n + 1, INF);

    // priority_queue 里存：
    // {当前距离, 点编号}
    //
    // greater<pair<...>> 使它变成小根堆
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // 这是一个已经过期的状态
        if (d != dist[u])
        {
            continue;
        }

        // 用 u 去更新它能到达的所有点
        for (auto edge : graph[u])
        {
            int v = edge.to;
            int w = edge.w;

            // 松弛
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;

                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INF)
        {
            cout << INT_MAX;
        }
        else
        {
            cout << dist[i];
        }

        if (i != n)
        {
            cout << ' ';
        }
    }

    return 0;
}