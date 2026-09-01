#include <bits/stdc++.h>
using namespace std;

struct Problem
{
    bool solved = false;
    int wrong = 0;
};

struct Team
{
    string name;

    int solved = 0;
    int penalty = 0;

    Problem prob[26];
};

struct Submission
{
    string team;
    char prob;
    int time;
    string result;
};

bool better(int solved1, int penalty1, int solved2, int penalty2)
{
    if (solved1 != solved2) return solved1 > solved2;

    return penalty1 < penalty2;
}

bool canWin(const Team& team, int bestSolved, int bestPenalty)
{
    if (team.solved != bestSolved) return team.solved > bestSolved;

    // 相同也可以并列冠军
    return team.penalty <= bestPenalty;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int s;
        cin >> s;

        vector<Submission> submissions(s);

        for (auto& sub : submissions)
        {
            cin >> sub.team >> sub.prob >> sub.time >> sub.result;
        }

        sort(submissions.begin(), submissions.end(),
             [](const Submission& a, const Submission& b) { return a.time < b.time; });

        unordered_map<string, int> id;
        vector<Team> teams;

        // 先把所有队伍建出来
        for (auto& sub : submissions)
        {
            if (!id.count(sub.team))
            {
                int newId = teams.size();

                id[sub.team] = newId;

                Team team;
                team.name = sub.team;

                teams.push_back(team);
            }
        }

        /*
            第一阶段：
            只处理封榜前确定的提交
        */
        for (auto& sub : submissions)
        {
            if (sub.result == "Unknown") continue;

            Team& team = teams[id[sub.team]];
            Problem& p = team.prob[sub.prob - 'A'];

            // 已经 AC 的题，后续提交全部无效
            if (p.solved) continue;

            if (sub.result == "Rejected")
            {
                p.wrong++;
            }
            else if (sub.result == "Accepted")
            {
                p.solved = true;

                team.solved++;

                team.penalty += sub.time + p.wrong * 20;
            }
        }

        /*
            找封榜时最强成绩
        */
        int bestSolved = -1;
        int bestPenalty = 0;

        for (auto& team : teams)
        {
            if (bestSolved == -1 || better(team.solved, team.penalty, bestSolved, bestPenalty))
            {
                bestSolved = team.solved;
                bestPenalty = team.penalty;
            }
        }

        /*
            第二阶段：

            为了求“每支队伍理论最好能打到什么成绩”，
            可以把所有 Unknown 都当作 Accepted。

            注意：
            我们并不是说现实里所有 Unknown 同时 AC。

            这里只是在同时计算：
            每支队伍各自那个最有利世界中的成绩。
        */
        for (auto& sub : submissions)
        {
            if (sub.result != "Unknown") continue;

            Team& team = teams[id[sub.team]];
            Problem& p = team.prob[sub.prob - 'A'];

            // 已经解决，后续提交无意义
            if (p.solved) continue;

            // 第一个 Unknown 直接假设 AC
            p.solved = true;

            team.solved++;

            team.penalty += sub.time + p.wrong * 20;
        }

        vector<string> ans;

        for (auto& team : teams)
        {
            if (canWin(team, bestSolved, bestPenalty))
            {
                ans.push_back(team.name);
            }
        }

        sort(ans.begin(), ans.end());

        for (int i = 0; i < (int)ans.size(); i++)
        {
            if (i) cout << ' ';

            cout << ans[i];
        }

        cout << '\n';
    }
}