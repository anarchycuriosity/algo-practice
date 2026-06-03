#include <iostream>
#include <vector>
int arr[1000][1000];
struct point
{
    int degree = 0;
    std::vector<int> edges;
};
int main()
{
    int n, m;  // n是顶点数，m是边数
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int start, end;
        std::cin >> start >> end;
        arr[start][end] = 1;
    }
    std::vector<point> points;
    for (int i = 1; i <= n; i++)
    {
        point p;
        points.push_back(p);
        for (int j = 1; j <= n; j++)
        {
            if (arr[i][j] != 0)
            {
                points[points.size() - 1].edges.push_back(j);
                points[points.size() - 1].degree++;
            }
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    if (!points.empty())
    {
        for (int i = 0; i < points.size(); i++)
        {
            if (points[i].degree != 0)
            {
                std::cout << points[i].degree << " ";
                for (int j = 0; j < points[i].degree; j++)
                {
                    std::cout << points[i].edges[j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}