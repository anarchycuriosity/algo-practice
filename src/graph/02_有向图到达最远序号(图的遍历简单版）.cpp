#include <cmath>
#include <iostream>
// 有向图求每个点到达的最远序号
int map[1001][1001];
int n, m;
// 反向建图进行有效剪枝
// 为什么反向建图，因为这个题目的方向是固定的
// 也就是找序号最大的点（这很关键）
// 我们反向让大数统治小数，这样先被统治（染色）的数一定是被它能到达的最大的数所统治
bool visit[1001];
int ans[1001];
int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int start, end;
        std::cin >> start >> end;
        map[start][end] = 1;  // 反向建图
    }

    for (int start = 1; start <= n; start++)
    {
    }
}