/*
看到相邻石子就可以想到线段dp了

错误想法:我只想到这是环形所以要取余,也许二维dp,维度可以从已经合并的石头总数,已经合并的堆数,还有位置来选,
我不确定然后现在可以来源于位置+-1,可是我不太明白合并之后应该处理石堆的位置,总不能用链表吧,或者我们根本不用真的删除,只是从原数组里面"拿"就好了
无论内部怎么合并，只要最终合成了一堆，它就永远代表：
[l,r]
假设 [l,r] 已经合并完成，那么它最后一步发生了什么？
这是区间 DP 特别重要的思考方式：
不问第一步做什么，问最后一步做什么。

对于环形一开始会想到取余,但对于环形DP来说,好像会比较痛苦
通常处理环形 DP 有一个经典技巧：
复制一遍数组,然后枚举n个起点,就像在不同位置剪掉这个环变成线

len 不是为了“枚举所有情况”本身，而是为了保证算大区间之前，小区间已经算完。
我要按照依赖关系，从小问题向大问题计算。
比如我想找(1,4),就需要(1,2)(3,4)等,但是这个东西还没有算出来,如果你没有算小长度的话
所以不应该这样写,因为很乱,比如你可能先算(1,4),但是(2,4)可能还没算
for (int l = 1; l <= n; l++)
    for (int r = l; r <= n; r++)

其实这里的dp完全就是线性dp,只有在复制和结尾更新答案的时候考虑了环
如果没有环,答案一次就出来了,但是环就需要枚举起点然后更新
*/
#include <bits/stdc++.h>
using namespace std;
// 而且一开始只给开了100,给少了,因为是2N,所以应该给200多
int min_dp[204][204];  // 不能一起在这里初始化为0,因为这是min_dp
int max_dp[204][204];
const int INF = 1e9;
int main()
{
    int N;
    cin >> N;
    // vector<int> tmp(N + 1);
    vector<int> stones(2 * N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> stones[i];
        stones[i + N] = stones[i];
    }
    for (int i = 1; i <= 2 * N; i++)
    {
        for (int j = 1; j <= 2 * N; j++)
        {
            min_dp[i][j] = INF;
        }
    }
    for (int i = 1; i <= 2 * N; i++)
    {
        min_dp[i][i] = 0;
        max_dp[i][i] = 0;
    }
    // 这里使用前缀和来算分数
    vector<int> prefix(2 * N + 1, 0);
    for (int i = 1; i <= 2 * N; i++)
    {
        prefix[i] = prefix[i - 1] + stones[i];
    }
    for (int len = 2; len <= N; len++)
    {
        // for (int start = 1; start <= N; start++)
        for (int start = 1; start + len - 1 <= 2 * N; start++)
        {
            // for (int k = start + 1; k < N; k++)
            int sum = prefix[start + len - 1] - prefix[start - 1];
            for (int k = start; k < start + len - 1; k++)
            {
                min_dp[start][start + len - 1] =
                    min(min_dp[start][k] + min_dp[k + 1][start + len - 1] + sum,
                        min_dp[start][start + len - 1]);  // 因为选择子石头加起来的时候,现在这一堆还没有合并
                max_dp[start][start + len - 1] =
                    max(max_dp[start][k] + max_dp[k + 1][start + len - 1] + sum, max_dp[start][start + len - 1]);
            }
        }
    }
    // int ans_min = INFINITY;
    int ans_min = INF;
    int ans_max = 0;
    for (int k = 1; k <= N; k++)
    {
        ans_min = min(ans_min, min_dp[k][k + N - 1]);
        ans_max = max(ans_max, max_dp[k][k + N - 1]);
    }
    cout << ans_min << "\n" << ans_max;
}