#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll INF = (1LL << 60);

struct Edge
{
    ll v;
    ll w;
};

// Bellman-Ford 需要知道一条边完整的 u, v, w
struct RawEdge
{
    ll u;
    ll v;
    ll w;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<RawEdge> edges;

    for (int i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    /*
        第一部分：求 h[]

        本来 Johnson 会新建一个超级源点 0：

            0 -> 1   权 0
            0 -> 2   权 0
            ...
            0 -> n   权 0

        然后从 0 跑 Bellman-Ford。

        因为 0 到每个点一开始都是 0，
        所以我们可以直接：

            h[i] = 0

        等价于把超级源点省略掉。
    */

    vector<ll> h(n + 1, 0);

    /*
        Bellman-Ford

        如果不存在负环，
        n 个点的最短路最多只需要 n-1 条边。

        所以如果第 n 轮仍然可以松弛，
        就说明存在负环。
    */

    for (int round = 1; round <= n; round++)
    {
        bool changed = false;

        for (auto edge : edges)
        {
            ll u = edge.u;
            ll v = edge.v;
            ll w = edge.w;

            // 松弛
            if (h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                changed = true;

                // 第 n 轮还能变短
                // 说明存在负环
                if (round == n)
                {
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }

        // 已经完全稳定了，后面不用继续跑
        if (!changed)
        {
            break;
        }
    }

    /*
        第二部分：重新建图

        原边：

            u -> v，权 w

        新边：

            w' = w + h[u] - h[v]

        由于 h[] 是最短路：

            h[v] <= h[u] + w

        所以：

            w + h[u] - h[v] >= 0

        新图所有边都非负。
    */

    vector<vector<Edge>> graph(n + 1);

    for (auto edge : edges)
    {
        ll u = edge.u;
        ll v = edge.v;
        ll w = edge.w;

        ll new_w = w + h[u] - h[v];

        graph[u].push_back({v, new_w});
    }

    /*
        第三部分：

        现在图里已经没有负边了。

        所以下面基本就是你原来的
        小根堆 Dijkstra。
    */

    for (int s = 1; s <= n; s++)
    {
        vector<ll> dist(n + 1, INF);

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

        dist[s] = 0;

        pq.push({0, s});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            /*
                旧数据不主动删除。

                如果：

                    原来 dist[u] = 10
                    push({10, u})

                后来：
                    dist[u] = 5
                    push({5, u})

                那么以后 {10,u} 出来的时候，
                它已经过期了。
            */
            if (d > dist[u])
            {
                continue;
            }

            for (auto edge : graph[u])
            {
                ll v = edge.v;
                ll w = edge.w;

                // 你熟悉的松弛
                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;

                    pq.push({dist[v], v});
                }
            }
        }

        /*
            第四部分：恢复原图距离

            新距离：

                dist'[s][v]

            满足：

                dist'[s][v]
                =
                dist[s][v] + h[s] - h[v]

            所以：

                原距离
                =
                新距离 - h[s] + h[v]
        */

        ll ans = 0;

        for (int v = 1; v <= n; v++)
        {
            if (dist[v] == INF)
            {
                // 题目规定不可达就是 1e9
                ans += 1LL * v * 1000000000LL;
            }
            else
            {
                ll real_dist = dist[v] - h[s] + h[v];

                ans += 1LL * v * real_dist;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}