#include <cmath>
#include <iostream>
// 有向图求每个点到达的最远序号
int map[1001][1001];
int n, m;
bool is_end(int cur)
{
    for (int next = 1; next <= n; next++)
    {
        if (map[cur][next] == 1)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int start, end;
        std::cin >> start >> end;
        map[start][end] = 1;
    }
    for (int start = 1; start <= n; start++)
    {
    }
}