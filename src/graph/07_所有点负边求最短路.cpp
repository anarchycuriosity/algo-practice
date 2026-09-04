/*
前 n-1 轮：
    给正常的最长简单路径足够的传播时间

第 n 轮：
    正常情况已经不可能继续变短
    如果还能变短，只可能因为负环
    所以bellman是以边为起点,每轮选到的那个边可能不会更新h,可能某个点在当前轮是未到达的状态,所以跑n个点基本要跑n -
1轮,最坏情况

而dijikstra是围绕着点及其相关的边来的,显然会更快因为确认每个点的最短路只需要常数条边

为什么要用new_w,而不能粗暴的给每个路径+10?这是因为每个路径走过的边数不一样

*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = (1LL << 60);
struct RawEdge
{
    ll u, v, w;
};
struct Edge
{
    ll v;
    ll w;
};
int main()
{  // 用bellman检查负环拿到h,超级原点
    ll n, m;
    cin >> n >> m;
    vector<RawEdge> raw_edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> raw_edges[i].u >> raw_edges[i].v >> raw_edges[i].w;
    }
    vector<ll> h(n + 1, 0);  // 超级原点到任何点都是0
    for (int i = 1; i <= n; i++)
    {
        bool changed = false;
        for (auto raw_edge : raw_edges)
        {
            ll u = raw_edge.u;
            ll v = raw_edge.v;
            ll w = raw_edge.w;
            if (h[v] > h[u] + w)
            {
                changed = true;
                h[v] = h[u] + w;
                if (i == n)
                {
                    cout << -1;
                    return 0;
                }
            }
        }
        if (!changed)
        {
            break;
        }
    }
    // 对于每个起点,进入循环,创建新的dist,当作单源最短路来写
    vector<vector<Edge>> graph(n + 1);  // dijikstra需要的带边的图,需要处理让新的w非负
    for (auto raw_edge : raw_edges)
    {
        ll u = raw_edge.u;
        ll v = raw_edge.v;
        ll w = raw_edge.w + h[u] - h[v];
        graph[u].push_back({v, w});
    }
    for (ll s = 1; s <= n; s++)
    {
        vector<ll> dist(n + 1, INF);
        dist[s] = 0;
        // priority_queue<Edge, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
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
                    pq.push({dist[v], v});  // 更新完不要忘记塞进去不然就没有意义了
                }
            }
        }
        ll ans = 0;
        for (ll j = 1; j <= n; j++)
        {
            if (dist[j] == INF)
            {
                ans += (ll)1 * j * (ll)(1e9);
            }
            else
            {
                ll real_w = dist[j] + h[j] - h[s];
                ans += (ll)1 * j * real_w;
            }
        }
        cout << ans << "\n";
    }
}
