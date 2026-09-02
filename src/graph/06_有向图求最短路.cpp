/*
旧的我不删,因为在优先队列中删除指定元素很麻烦
新的直接塞进去
以后旧的出来的时候，再判断一下是不是过期。
为什么这样得到的路径会是最短路,因为我总是拿最短的权出来,先到的点肯定最短
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Edge
{
    ll v;
    ll w;
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++)  // 读边的时候写错成了n
    {
        Edge edge;
        ll u;
        cin >> u >> edge.v >> edge.w;
        graph[u].push_back(edge);
    }
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    const ll INF = ((ll)1 << 31) - 1;
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;  // 从原点开始扩散,然后利用pq优化dist
    pq.push({0, s});
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
        {
            continue;
        }
        for (auto edge : graph[u])
        {
            ll v = edge.v;
            ll w = edge.w;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
}
