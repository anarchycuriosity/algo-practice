#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

struct path_node
{
    long long steps;
    std::string path;
};

// 比较两个路径，返回 true 如果 a 优于 b
bool is_better(const path_node& a, const path_node& b)
{
    if (a.steps != b.steps)
    {
        return a.steps < b.steps;
    }
    return a.path < b.path;
}

std::unordered_map<long long, path_node> memo;

path_node find_best_sequence(long long x)
{
    if (x == 1)
    {
        return path_node{0, ""};
    }

    if (memo.find(x) != memo.end())
    {
        return memo[x];
    }

    path_node result;

    if (x % 2 == 0)
    {
        path_node prev = find_best_sequence(x / 2);
        if (x == 2)
        {
            result = path_node{prev.steps + 1, prev.path + "A"};
        }
        else
            result = path_node{prev.steps + 1, prev.path + "B"};
    }
    else
    {
        // 分支 A: 从 x-1 变换而来 (正向操作为 +1, 即 A)
        path_node prev_down = find_best_sequence(x - 1);
        path_node option_a = path_node{prev_down.steps + 1, prev_down.path + "A"};

        // 分支 C: 从 x+1 变换而来 (正向操作为 -1, 即 C)
        path_node prev_up = find_best_sequence(x + 1);
        path_node option_c = path_node{prev_up.steps + 1, prev_up.path + "C"};

        if (is_better(option_a, option_c))
        {
            result = option_a;
        }
        else
        {
            result = option_c;
        }
    }

    memo[x] = result;
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long target_distance = 0;
    if (std::cin >> target_distance)
    {
        path_node ans = find_best_sequence(target_distance);
        std::cout << ans.steps << "\n";
        std::cout << ans.path << "\n";
    }

    return 0;
}