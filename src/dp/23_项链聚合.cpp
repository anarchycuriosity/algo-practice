#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll NEG_INF = -1e9;
struct Jew
{
    ll head = NEG_INF;
    ll butt = NEG_INF;
};
struct Unit
{
    Jew jew;
    ll power = NEG_INF;
    Unit(ll head, ll butt, ll power)
    {
        this->jew.head = head;
        this->jew.butt = butt;
        this->power = power;
    }
};
ll get_power(Jew& a, Jew& b) { return a.head * a.butt * b.butt; }
int main()
{
    int N;
    cin >> N;
    vector<Jew> jews(2 * N + 1, {0, 0});
    int cpn = 2 * N;
    for (int i = 1; i <= N; i++)
    {
        cin >> jews[i].head;
    }
    for (int i = 1; i < N; i++)
    {
        jews[i].butt = jews[i + 1].head;
    }
    jews[N].butt = jews[1].head;
    for (int i = 1; i <= N; i++)
    {
        jews[i + N].butt = jews[i].butt;
        jews[i + N].head = jews[i].head;
    }
    // 没有聚合能量为0
    // vector<vector<Unit>> dp(cpn + 1, vector<Unit>(cpn + 1));
    // vector<vector<Jew>> dp(cpn + 1, vector<Jew>(cpn + 1));
    vector<vector<ll>> dp(cpn + 1, vector<ll>(cpn + 1, 0));
    ll total = 0;
    for (int len = 2; len <= cpn; len++)
    {
        for (int start = 1; start + len - 1 <= cpn; start++)
        {
            for (int k = start; k < start + len - 1; k++)
            {
                int end = start + len - 1;
                dp[start][end] = max(dp[start][end],
                                     jews[start].head * jews[k].butt * jews[end].butt + dp[start][k] + dp[k + 1][end]);
            }
        }
    }
    for (int k = 1; k <= N; k++)
    {
        total = max(total, dp[k][k + N - 1]);
    }
    cout << total;
}