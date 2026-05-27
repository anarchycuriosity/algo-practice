#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int station_count = 0;
    if (!(std::cin >> station_count))
    {
        return 0;
    }

    // 使用二维数组存储租金，大小为 (n+1) x (n+1)
    std::vector<std::vector<int>> rent_matrix(station_count + 1, std::vector<int>(station_count + 1, 0));

    // 读入上三角租金矩阵
    for (int i = 1; i < station_count; ++i)
    {
        for (int j = i + 1; j <= station_count; ++j)
        {
            std::cin >> rent_matrix[i][j];
        }
    }

    // min_cost[i] 表示从 1 号站到 i 号站的最少租金
    const int infinity = 1e9;
    std::vector<int> min_cost(station_count + 1, infinity);
    min_cost[1] = 0;

    // 动态规划状态转移
    for (int i = 2; i <= station_count; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (min_cost[j] + rent_matrix[j][i] < min_cost[i])
            {
                min_cost[i] = min_cost[j] + rent_matrix[j][i];
            }
        }
    }

    std::cout << min_cost[station_count] << std::endl;

    return 0;
}