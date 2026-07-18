#include <iostream>
#include <string>
#include <vector>
std::string abbr(std::string word)
{
    int size = word.size();
    if (size > 10)
    {
        size -= 2;
        char front = word.front();
        char back = word.back();
        std::string result;
        result += std::string(1, front);
        result += std::to_string(size);
        result += std::string(1, back);
        /*
            result.push_back(front).push_back(std::tostring(size));
        */
        return result;
    }
    return word;
}
int main()
{
    std::string str;
    int count;
    std::cin >> count;
    std::vector<std::string> ans;
    while (count--)
    {
        std::cin >> str;
        ans.push_back(abbr(str));
    }
    for (int i = 0; i < ans.size(); i++)
    {
        std::cout << ans[i] << "\n";
    }
}