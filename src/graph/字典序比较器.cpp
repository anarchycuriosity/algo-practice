#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Node
{
    ll dist;
    ll u;
    ll type;
};

struct Compare
{
    bool operator()(const Node& a, const Node& b) const
    {
        if (a.dist != b.dist) return a.dist > b.dist;

        if (a.u != b.u) return a.u > b.u;

        return a.type > b.type;
    }
};

priority_queue<Node, vector<Node>, Compare> pq;

// struct Node
// {
//     ll a, b, c;
// };

// bool cmp(const Node& x, const Node& y)
// {
//     if (x.a != y.a) return x.a > y.a;
//     if (x.b != y.b) return x.b > y.b;
//     return x.c > y.c;
// }

// int main()
// {
//     priority_queue<Node, vector<Node>, decltype(&cmp)> pq(cmp);

//     pq.push({1, 2, 3});
//     pq.push({1, 1, 5});
//     pq.push({0, 9, 9});
// }