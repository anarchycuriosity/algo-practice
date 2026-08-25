/*
空格会贡献负的相似度
相同才会贡献正的相似度,相异也是负的相似度
那就只能相异的用空格分开咯
但是相异的话,如果插入空格去控制的话,有可能会产生一些相同的
开一个新 gap 扣 A，继续已有 gap 只扣 B。
因此我们必须知道：
上一步是不是已经在空格段里面。

不要盯着空格那个公式看,而是这样
第 1 个空格：-A
第 2 个空格：-B
第 3 个空格：-B
第 4 个空格：-B
...
两个历史能不能合并成一个 DP 状态，不是看它们现在是不是到达同一个 (i,j)
要看的是：它们对未来的影响是否完全相同。

想法:不要在原字符串插入,而是用两个指针在原字符串上滑动,然后选or不选丢到新的两个字符串上,甚至这两个新的字符串可以不存在

插空格方案很多
↓
但可以从左往右一列一列构造
↓
每一列只会消费：
(i-1,j-1)
(i-1,j)
(i,j-1)
↓
所以天然适合前缀 DP
↓
尝试 dp[i][j]
↓
发现加入空格时，不知道应该扣 A 还是 B
↓
为什么不知道？
因为不知道上一列是不是同方向空格
↓
说明 dp[i][j] 丢失了会影响未来的信息
↓
那么未来到底需要知道多少历史？
只需要知道最后一列类型
↓
最后一列只有三种：
字符/字符
字符/-
-/字符
↓
所以拆成 M、X、Y 三个状态
↓
新开 gap 扣 A
继续同方向 gap 扣 B
↓
转移自然得到
*/

#include <bits/stdc++.h>
using namespace std;
const int NEG = (int)-1e9;
int id(char ch)
{
    if (ch == 'A')
    {
        return 0;
    }
    else if (ch == 'T')
    {
        return 1;
    }
    else if (ch == 'G')
    {
        return 2;
    }
    else
    {
        return 3;
    }
}
int main()
{
    string s;
    string t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    int d[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> d[i][j];
        }
    }
    int A, B;
    cin >> A >> B;
    vector<vector<int>> M(n + 1, vector<int>(m + 1, NEG));
    vector<vector<int>> X(n + 1, vector<int>(m + 1, NEG));
    vector<vector<int>> Y(n + 1, vector<int>(m + 1, NEG));
    M[0][0] = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            // int score = d[id(s[i - 1])][id(t[j - 1])];
            if (i > 0 && j > 0)
            {
                int score = d[id(s[i - 1])][id(t[j - 1])];
                M[i][j] = max({M[i - 1][j - 1], X[i - 1][j - 1], Y[i - 1][j - 1]}) + score;
            }
            if (i > 0)
            {
                X[i][j] = max({M[i - 1][j] - A, X[i - 1][j] - B, Y[i - 1][j] - A});
            }
            if (j > 0)
            {
                Y[i][j] = max({M[i][j - 1] - A, X[i][j - 1] - A, Y[i][j - 1] - B});
            }
        }
    }
    cout << max({M[n][m], X[n][m], Y[n][m]});
}
