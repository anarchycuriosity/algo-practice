// 尝试逆向思维，不要把定义看的太死盲目打表
// 闭合圆圈的定义并不一定就如题：圈里面的0出不去，也可以是外面的0进不来
#include <iomanip>
#include <iostream>
#include <queue>
int area[30][30];
int move1[] = {1, 1, -1, -1};
int move2[] = {-1, 1, -1, 1};
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
    q.push({0, 0});
    q.push({0, n - 1});
    q.push({n - 1, n - 1});
    q.push({n - 1, 0});
    while (!q.empty())
    {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int next_x = curx + move1[i];
            int next_y = cury + move2[i];
            if (next_x >= n || next_y >= n || area[next_x][next_y] == 1)
            {
                continue;
            }
            area[next_x][next_y] = -1;
            q.push({next_x, next_y});
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
                std::cout << std::setw(3) << 0;
            }
            else
            {
                std::cout << std::setw(3) << area[i][j];
            }
        }
        std::cout << "\n";
    }
}