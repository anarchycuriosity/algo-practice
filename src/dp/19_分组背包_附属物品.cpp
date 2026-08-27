#include <bits/stdc++.h>
using namespace std;
struct Attachment
{
    int cost;
    int contri;
};
struct Item
{
    int cost;
    int contri;
    vector<Attachment> attach;
};
// 不能先更新“主”，然后拿更新后的结果继续更新“主+附件”
int main()
{
    int capa, m;
    cin >> capa >> m;
    vector<Item> items(m + 1);
    vector<int> q(m + 1);  // 物品依附的主键的编号
    for (int i = 1; i <= m; i++)
    {
        int cost, import;
        cin >> cost >> import >> q[i];
        if (q[i] == 0)
        {
            items[i].cost = cost;
            items[i].contri = cost * import;
        }
        else
        {
            items[q[i]].attach.push_back({cost, cost * import});
        }
    }
    vector<int> dp(capa + 1, 0);
    // vector<pair<int, int>> choices;这是在每个主键之内的
    for (auto& item : items)
    {
        vector<pair<int, int>> choices;
        // if(item.attach.size() == 0)主键肯定要买的,所以不用判断了
        int cost = item.cost;
        int contri = item.contri;
        choices.push_back({cost, contri});
        if (item.attach.size() == 1)
        {
            cost = item.cost + item.attach[0].cost;
            contri = item.contri + item.attach[0].contri;
            choices.push_back({cost, contri});
        }
        else if (item.attach.size() > 1)
        {
            // 主和1
            cost = item.cost + item.attach[0].cost;
            contri = item.contri + item.attach[0].contri;
            choices.push_back({cost, contri});
            // 主和2
            cost = item.cost + item.attach[1].cost;
            contri = item.contri + item.attach[1].contri;
            choices.push_back({cost, contri});
            // 主和1和2
            cost = item.cost + item.attach[0].cost + item.attach[1].cost;
            contri = item.contri + item.attach[0].contri + item.attach[1].contri;
            choices.push_back({cost, contri});
        }
        for (int i = capa; i >= 0; i--)  // 第一轮循环应该是capa而不是item
        {
            for (auto& choice : choices)
            {
                if (i - choice.first >= 0)
                {
                    dp[i] = max(dp[i], dp[i - choice.first] + choice.second);
                }
            }
        }
    }

    cout << dp[capa];
}