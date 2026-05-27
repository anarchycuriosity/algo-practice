// 边权为1，代价相同，先走到的位置一定是步数最少的
#include <stdio.h>
#include <string.h>

#include <iomanip>
#include <iostream>
#include <queue>
bool visited[400][400];  // 是否访问
int record[400][400];    // 记录走的步数
// 这个好像是base1
// 好好读题，因为有些地方马走不到，所以标记为-1。初始化的区域一开始都是去不到的
// 反正后面会覆盖，其实初始化的值没什么影响
int move1[] = {1, 1, -1, -1, 2, 2, -2, -2};
int move2[] = {2, -2, 2, -2, 1, -1, 1, -1};
int main()
{
    int n, m, x, y;
    std::cin >> n >> m >> x >> y;
    memset(record, -1, sizeof(record));
    std::queue<std::pair<int, int>> q;
    // 一开始把起点推进去就好了
    q.push({x, y});
    record[x][y] = 0;
    visited[x][y] = true;
    while (!q.empty())
    {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int nextx = curx + move1[i];
            int nexty = cury + move2[i];
            if (nextx >= 1 && nextx <= n && nexty >= 1 && nexty <= m && visited[nextx][nexty] == false)
            {
                visited[nextx][nexty] = true;
                q.push({nextx, nexty});
                record[nextx][nexty] = record[curx][cury] + 1;
            }
        }
    }
    // 空5格
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cout << std::setw(5) << record[i][j];
        }
        std::cout << "\n";
    }
}
