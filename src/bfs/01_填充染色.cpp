// 尝试逆向思维，不要把定义看的太死盲目打表
// 闭合圆圈的定义并不一定就如题：圈里面的0出不去，也可以是外面的0进不来
#include <iomanip>
#include <iostream>
#include <queue>
int area[30][30];
bool vis[30][30];
int move1[] = {0, 1, -1, 0, 0};
int move2[] = {0, 0, 0, -1, 1};
int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> area[i][j];
        }
    }
    std::queue<std::pair<int, int>> q;
    // 不仅仅是四个端点入q，而是四个边，忘记了。。
    //  q.push({0, 0});
    //  q.push({0, n - 1});
    //  q.push({n - 1, n - 1});
    //  q.push({n - 1, 0});
    // 两个for加个判断即可
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                if (area[i][j] == 0)
                {
                    q.push({i, j});
                    vis[i][j] = true;
                    area[i][j] = -1;
                }
            }
        }
    }
    while (!q.empty())
    {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        for (int i = 0; i < 5; i++)
        {
            int next_x = curx + move1[i];
            int next_y = cury + move2[i];
            // 有上界判定但缺少下界
            // 不需要判断是否遇到1，只要看是否是0即可
            // if (next_x < 0 || next_x >= n || next_y >= n || next_y < 0 || area[next_x][next_y] == 1 ||
            //     vis[next_x][next_y] == true)
            if (next_x < 0 || next_x >= n || next_y >= n || next_y < 0)
            {
                continue;
            }
            // 不用判断撞墙，只要判断是0即可
            if (area[next_x][next_y] == 0)
            {
                area[next_x][next_y] = -1;
                q.push({next_x, next_y});
                vis[next_x][next_y] = true;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (area[i][j] == 0)
            {
                area[i][j] = 2;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (area[i][j] == -1)
            {
                std::cout << 0 << " ";
            }
            else
            {
                std::cout << area[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}