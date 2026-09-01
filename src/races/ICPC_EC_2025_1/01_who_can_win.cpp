#include <bits/stdc++.h>
using namespace std;
#define ll long long
/*
不对!可能赢只需要以一个队伍作为核心来考虑,让他的unknown全对,别人的unknow全错!
*/
struct Team
{
    unordered_map<string, int> solved;
    string id;
    int possi = 0;
    int certain = 0;
    int time = 0;
};
struct Input
{
    string id;
    string prob;
    int time;
    string type;
};
bool comp(Input& a, Input& b)
{
    if (a.time == b.time)
    {
        return a.id < b.id;
    }
    return a.time < b.time;
}
bool judge(Team& a, Team& b)
{
    if (a.possi == b.possi)
    {
        if (a.certain == b.certain)
        {
            return a.time < b.time;
        }
        return a.certain > b.certain;
    }
    return a.possi > b.possi;
}
int main()
{
    int r;
    cin >> r;
    vector<vector<string>> anses;
    while (r--)
    {
        int s;
        cin >> s;
        unordered_map<string, Team> possi_map;
        vector<Input> inputs(s);
        for (int i = 0; i < s; i++)
        {
            cin >> inputs[i].id >> inputs[i].prob >> inputs[i].time >> inputs[i].type;
        }
        sort(inputs.begin(), inputs.end(), comp);
        for (Input input : inputs)
        {
            if (input.type == "Rejected")
            {
                possi_map[input.id].time += 20;
            }
            else if (input.type == "Accepted")
            {
                possi_map[input.id].solved[input.prob] = 1;
                possi_map[input.id].possi++;
                possi_map[input.id].certain++;
            }
            else if (input.type == "Unknown")
            {
                if (possi_map[input.id].solved[input.prob] == 0)
                {
                    possi_map[input.id].solved[input.prob] = -1;
                    possi_map[input.id].possi++;
                }
                else
                {
                    continue;
                }
            }
        }
        vector<Team> teams(0);
        int team_i = 0;
        for (auto team : possi_map)
        {
            teams[team_i].id = team.first;
            teams[team_i].certain = team.second.certain;
            teams[team_i].possi = team.second.possi;
            teams[team_i].time = team.second.time;
            team_i++;
        }
        sort(teams.begin(), teams.end(), judge);
        vector<string> ans;
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i].certain > teams[i + 1].certain)
            {
                break;
            }
            ans.push_back(teams[i].id);
        }
        sort(ans.begin(), ans.end());
        anses.push_back(ans);
    }
    for (int i = 0; i < anses.size(); i++)
    {
        for (int j = 0; j < anses[i].size(); j++)
        {
            cout << anses[i][j] << " ";
        }
        cout << "\n";
    }
}