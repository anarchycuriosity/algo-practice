# 2026 ICPC 网络预选赛康复训练计划

## 0. 现实判断

今天是 2026-07-18，距离第一场网络预选赛 2026-09-06 还有 50 天，距离第二场 2026-09-12 还有 56 天。

官方时间源：

- ICPC 北京总部公告：2026-2027 赛季网络预选赛安排在 2026-09-06（周日）和 2026-09-12（周六）。
- Codeforces 当前可参加比赛：Codeforces Round 1111 (Div. 2)，2026-07-18 22:35（北京时间），时长 2 小时。

关于“以前写过题，现在完全忘了”：这是正常现象。算法训练不是背诵型知识，更接近运动技能。停一段时间后，最先掉的是：

- 题型识别速度：看不出这是二分、贪心、图搜索还是 DP。
- 代码肌肉记忆：边界、初始化、数组大小、`long long`、输入输出细节变慢。
- 比赛节奏：卡题、罚时、换题、读英文题面的能力会退化。

但不会完全归零。你本地仓库里已经有背包、BFS、Floyd、堆、快速幂、图存储、最短路等痕迹；洛谷通过题单也显示你已经通过过二分、贪心、搜索、背包、堆、并查集、区间 DP、模拟和字符串处理类题。你的问题不是“从零学习”，而是“唤醒旧技能 + 补比赛稳定性 + 把散乱经验整理成可调用模型”。不要用“我都忘了”吓自己，当然也别用“我以前会”麻痹自己。哼，事实就是这么无情。

## 1. 当前洛谷画像

### 已经做过的能力块

根据你给出的通过题单，可以暂时判断：

- 语法与基础模拟：数量足够，不需要再系统刷入门题。
- 基础数学：做过 P1035、P1304、P1422、P1720、P1980、P3383 等，能恢复筛法、枚举、取模和简单数论。
- 二分与单调性：通过 P1024、P1873，尝试过 P2241；二分基础存在，但需要强化“答案二分”和边界稳定性。
- 贪心：通过 P1090、P1223、P1803、P2240、P3817、P5019，说明贪心不是空白，但需要补证明意识。
- 搜索：通过 P1162、P1443、P1135、P1219、P1706，说明 BFS/DFS 能恢复，不需要从“队列是什么”开始。
- 动态规划：通过 P1048、P1216、P1616、P1855、P1719、P1775、P1833，说明 01 背包、完全背包、二维费用、区间 DP 都接触过。当前重点不是“第一次学 DP”，而是重建状态定义能力。
- 数据结构：通过 P3378、P3370、P1540、P1551、P2814，说明堆、哈希/集合、并查集都有基础。
- 图论：通过 B4292、P2910，图论覆盖偏薄；Dijkstra、拓扑、最小生成树、连通性需要重点补。

### 尝试过但未通过或需回炉的题

这些题要进入“错题回炉池”，不是立刻全做：

- 第一优先级，1 周内回炉：P1012、P1157、P1226、P2058、P3612。
- 第二优先级，2 周内回炉：P1217、P1480、P2241。
- 第三优先级，穿插处理：P1151。

优先级理由：

- P1226 是快速幂，属于数学和取模的基础工具，不能拖。
- P2058 是队列/滑动窗口，网络赛模拟题很常见。
- P1012 训练自定义比较，能补字符串与排序思维。
- P1157 训练 DFS 生成组合，是搜索的基本动作。
- P3612 训练递归定位，能防止遇到“大字符串不能真构造”的题时盲目模拟。

结论：入门题不再作为主线。后续训练应以“普及+/提高- 的基础板块 + CF Div.2 B/C/D”为主，入门题只用于赛前热手。

### 后续选题硬规则

从 2026-07-18 开始，题单按下面比例执行：

- 已通过题：不超过 20%，只用于限时校准和恢复模板。
- 尝试过但未通过题：约 20%，用于修补旧坑。
- 全新知识点题：至少 60%，用于补体系缺口。

每个专题必须至少包含一个“新模型题”，不能只重刷旧题。所谓新模型题，就是你做完后能新增一个判断信号，例如“看到区间加减要想到差分”，“看到动态前缀频率要想到树状数组”，“看到每个位置左边/右边第一个更大要想到单调栈”。

## 2. 训练总目标

### 网络预选赛最低可执行目标

到 2026-09-06 前，个人应达到：

- 能在 2 小时内稳定做完 CF Div.2 A、B，部分 C。
- 能在 5 小时 ICPC 赛制中稳定承担签到、模拟、简单贪心、二分、基础图搜索、基础 DP。
- 能看懂常见英文题面，不因为输入输出、样例解释、数据范围判断失误而丢题。
- 能在 15 分钟内判断一道题是否值得继续推进，避免“死磕一题毁全场”。

### 训练结构

训练不按“知识点全覆盖”线性推进，而按三个循环推进：

1. 恢复循环：每天 3~5 道基础题，恢复代码速度。
2. 专题循环：每 2~3 天一个主题，补回算法框架。
3. 比赛循环：每周至少 1 场 CF 或 VP，赛后必须补题和复盘。

## 3. 阶段安排

### 第一阶段：2026-07-17 到 2026-07-31，康复与测速

核心任务：

- 恢复 C++ 写题手感。
- 重建基础模板：排序、前缀和、二分、贪心、BFS、DFS、堆、并查集、Dijkstra、背包。
- 已通过题不默认重刷；只有当它能作为“限时复健题”时才重做，目标是 15~25 分钟 AC。
- 开始 CF，别等“准备好了”再打。比赛经验本身就是训练材料。

验收标准：

- 洛谷橙/黄题能稳定 AC。
- CF 800~1100 rating 题可以在 20~40 分钟内完成。
- 每场比赛能完成至少 2 题，赛后补到 3~4 题。

### 第二阶段：2026-08-01 到 2026-08-21，专题补强

核心专题：

- 二分答案与单调性。
- 贪心交换论证。
- BFS/DFS/连通块/拓扑排序。
- 最短路与最小生成树。
- 背包、线性 DP、区间 DP。
- 数据结构：堆、并查集、树状数组、ST 表。

验收标准：

- 每个专题至少 12~18 题。
- 能写出模板，但不依赖模板盲套。
- CF Div.2 C 有明显推进能力。

### 第三阶段：2026-08-22 到 2026-09-05，赛前压强模拟

核心任务：

- 每周 2 场 3~5 小时 VP。
- 每场赛后建立“错因表”：读错题、想错方向、代码错、复杂度错、不会知识点。
- 重点补网络赛常见杂题：构造、数学、字符串、图论、DP 混合题。

验收标准：

- 5 小时训练赛能稳定产出 3~5 题。
- 对题目有分层判断：签到题、可推题、模板题、暂时放弃题。

### 第四阶段：2026-09-06 到 2026-09-12，双赛维护

第一场网络赛后不要大改体系，只做：

- 复盘第一场暴露的问题。
- 补最痛的 1~2 个专题。
- 维持手感，不熬夜爆刷。

## 4. 本周详细安排

本周从 2026-07-18（周六）开始执行，到 2026-07-24（周五）结束。目标不再是“多刷简单题找手感”，而是“每天补一个体系缺口”。已通过题只保留少量限时校准，约占本周链接数的 20% 以内。

### 2026-07-18 周六：CF 入场 + 数学工具回炉

今天晚上有比赛，白天不堆重题，只做两个工具型题目，把提交环境和快速幂补回来。

白天任务，最多 90 分钟：

- [洛谷 P1226 快速幂](https://www.luogu.com.cn/problem/P1226)：尝试过，必须回炉。验收点：会写二进制快速幂，能解释为什么每次指数右移。
- [洛谷 P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：新题，数论工具。验收点：理解费马小定理/线性递推至少一种写法。
- [CF 1352C K-th Not Divisible by n](https://codeforces.com/problemset/problem/1352/C)：新题，数学 + 二分直觉，难度比纯签到高一点。

晚上比赛：

- [Codeforces Round 1111 (Div. 2)](https://codeforces.com/contest/2247)
- 时间：2026-07-18 22:35，北京时间。
- 目标：A、B 稳住，C 至少形成完整思路；不要因为一道题卡住超过 35 分钟。

赛后记录：

- 哪题是知识不会？
- 哪题是读题慢？
- 哪题是代码实现慢？

### 2026-07-19 周日：CF 补题 + 前缀/差分/双指针

先补 CF，再开专题。你缺的不是“会不会循环”，而是看到区间、连续段、计数时能不能立刻选模型。

CF 补题：

- 补 [Codeforces Round 1111 (Div. 2)](https://codeforces.com/contest/2247) 的 A、B、C。
- 如果 C 已过，读 D 的题解并写 5 行以内模型总结。

新知识点题：

- [洛谷 P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)：新题，差分。判断信号：大量区间经过次数统计。
- [洛谷 P3397 地毯](https://www.luogu.com.cn/problem/P3397)：新题，二维差分。判断信号：矩形加法，最后统一还原。
- [CF 279B Books](https://codeforces.com/problemset/problem/279/B)：新题，双指针/滑动窗口。判断信号：连续区间和不超过某值。
- [CF 1538C Number of Pairs](https://codeforces.com/problemset/problem/1538/C)：新题，排序 + 二分计数。判断信号：数对和落在区间内。

旧题占比控制：

- [洛谷 P2058 海港](https://www.luogu.com.cn/problem/P2058)：尝试过，作为滑动窗口回炉；如果当天前 4 题已完成，可以做，否则顺延。

### 2026-07-20 周一：二分答案 + 贪心证明

目标不是会写 `while (l <= r)`，而是会找单调性和 `check` 的含义。

新知识点题：

- [洛谷 P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：新题，二分答案。判断信号：最大化最小值。
- [洛谷 P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：新题，二分答案。判断信号：最小化最大段和。
- [CF 1201C Maximum Median](https://codeforces.com/problemset/problem/1201/C)：新题，二分/贪心。判断信号：用有限资源提高中位数。
- [CF 545C Woodcutters](https://codeforces.com/problemset/problem/545/C)：新题，贪心。判断信号：局部选择要给后面留空间。

少量校准题：

- [洛谷 P1873 砍树](https://www.luogu.com.cn/problem/P1873)：已通过，20 分钟限时复健；如果超时，说明二分模板还没恢复。

当天验收：

- 每题写出 `check(x)` 的含义。
- 至少给 P545C 写一句交换/不后悔解释。

### 2026-07-21 周二：单调栈/单调队列/堆

你的题单里有堆，但几乎没有单调结构。网络赛很爱用这些结构做“线性扫一遍”的优化。

新知识点题：

- [洛谷 P5788 单调栈](https://www.luogu.com.cn/problem/P5788)：新题，单调栈模板。判断信号：找右侧第一个更大元素。
- [洛谷 P1886 滑动窗口 / 单调队列](https://www.luogu.com.cn/problem/P1886)：新题，单调队列模板。判断信号：固定长度窗口最值。
- [洛谷 P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)：新题，前缀和 + 单调队列。判断信号：长度受限的最大子段和。
- [CF 372C Watching Fireworks is Fun](https://codeforces.com/problemset/problem/372/C)：挑战题，DP + 单调队列优化；当天可以只读懂转移，不强求 AC。

少量校准题：

- [洛谷 P3378 堆](https://www.luogu.com.cn/problem/P3378)：已通过，15 分钟限时复健。

当天验收：

- 能说清楚单调栈里弹出的元素为什么以后不会再有用。
- 能说清楚单调队列下标过期条件是什么。

### 2026-07-22 周三：树状数组/线段树入门

这是你体系里很明显的缺口。你做过一些排序、哈希、堆、并查集，但区间查询和动态维护还没成体系。

新知识点题：

- [洛谷 P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)：新题，单点加、区间和。
- [洛谷 P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)：新题，区间加、单点查，差分思想接树状数组。
- [洛谷 P1198 最大数](https://www.luogu.com.cn/problem/P1198)：新题，线段树维护区间最大值。
- [洛谷 P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)：新题，区间加、区间和、懒标记。

CF 加练：

- [CF 474B Worms](https://codeforces.com/problemset/problem/474/B)：新题，前缀和 + 二分，作为数据结构前的轻量计数题。

当天验收：

- 树状数组必须能解释 `lowbit(x)`。
- 线段树必须能解释 `push_down` 什么时候需要做。

### 2026-07-23 周四：图论补缺，拓扑/Dijkstra/Kruskal

你通过过一点图题，但图论体系偏薄。本日不再只写并查集模板，而是补“建图后如何推进状态”。

新知识点题：

- [洛谷 P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)：新题，拓扑排序 + DAG DP。
- [洛谷 P1113 杂务](https://www.luogu.com.cn/problem/P1113)：新题，拓扑排序求最早完成时间。
- [洛谷 P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：新题，优先队列 Dijkstra。
- [CF 20C Dijkstra?](https://codeforces.com/problemset/problem/20/C)：新题，Dijkstra + 路径还原。
- [洛谷 P3366 最小生成树](https://www.luogu.com.cn/problem/P3366)：新题，Kruskal。

少量校准题：

- [洛谷 P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：已通过，10 分钟并查集热身。

当天验收：

- 拓扑题要写出入度变化表。
- Dijkstra 要能解释 `priority_queue` 里为什么可能有过期状态。
- Kruskal 要能解释为什么按边权从小到大选。

### 2026-07-24 周五：DP 缺口与小模拟

你做过背包和区间 DP，但还缺 LIS、状态机 DP、树形 DP 这些比赛常见模型。

上午/下午 DP 专题：

- [洛谷 P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：新题，LIS/贪心二分。
- [洛谷 P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)：新题，LCS 转 LIS。
- [洛谷 P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：新题，树形 DP。
- [CF 455A Boredom](https://codeforces.com/problemset/problem/455/A)：新题，值域 DP。

晚上 2 小时混合训练，从下面选 4 题，不看题解：

- [CF 550C Divisibility by Eight](https://codeforces.com/problemset/problem/550/C)：构造/枚举。
- [CF 580C Kefa and Park](https://codeforces.com/problemset/problem/580/C)：树 DFS。
- [CF 510B Fox And Two Dots](https://codeforces.com/problemset/problem/510/B)：网格 DFS 找环。
- [洛谷 P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)：如果周三没稳，拿来复测。
- [洛谷 P5788 单调栈](https://www.luogu.com.cn/problem/P5788)：如果周二没稳，拿来复测。

周复盘模板：

周复盘模板：

- 本周 AC 数：
- 独立 AC 数：
- 看题解后 AC 数：
- 最常见错误：
- 下周必须补的专题：
- CF 比赛实际完成题数：

## 5. 知识缺口题库

本题库用于后续 3~5 周滚动抽题。每个模块先做 3~5 题建立模型，再进入混合训练。不要一个模块连刷 20 题，那样短期看起来很勤奋，长期会造成识别能力偏科。

### 前缀、差分、双指针

- [洛谷 P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)：差分。
- [洛谷 P3397 地毯](https://www.luogu.com.cn/problem/P3397)：二维差分。
- [CF 279B Books](https://codeforces.com/problemset/problem/279/B)：双指针。
- [CF 1538C Number of Pairs](https://codeforces.com/problemset/problem/1538/C)：排序 + 二分计数。
- [CF 466C Number of Ways](https://codeforces.com/problemset/problem/466/C)：前缀和计数，偏难。

### 二分答案与贪心

- [洛谷 P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：最大化最小值。
- [洛谷 P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：最小化最大值。
- [CF 1201C Maximum Median](https://codeforces.com/problemset/problem/1201/C)：二分/贪心。
- [CF 545C Woodcutters](https://codeforces.com/problemset/problem/545/C)：贪心。
- [CF 1613C Poisoned Dagger](https://codeforces.com/problemset/problem/1613/C)：二分答案。

### 单调结构

- [洛谷 P5788 单调栈](https://www.luogu.com.cn/problem/P5788)：单调栈模板。
- [洛谷 P1886 滑动窗口 / 单调队列](https://www.luogu.com.cn/problem/P1886)：单调队列模板。
- [洛谷 P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)：前缀和 + 单调队列。
- [洛谷 P2629 好消息，坏消息](https://www.luogu.com.cn/problem/P2629)：环形前缀 + 单调队列。
- [CF 372C Watching Fireworks is Fun](https://codeforces.com/problemset/problem/372/C)：DP + 单调队列优化，挑战题。

### 树状数组与线段树

- [洛谷 P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)：单点加、区间查。
- [洛谷 P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)：区间加、单点查。
- [洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：树状数组/归并排序。
- [洛谷 P1198 最大数](https://www.luogu.com.cn/problem/P1198)：线段树维护最大值。
- [洛谷 P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)：懒标记。

### 图论

- [洛谷 P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)：拓扑排序 + DAG DP。
- [洛谷 P1113 杂务](https://www.luogu.com.cn/problem/P1113)：拓扑排序。
- [洛谷 P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：Dijkstra。
- [CF 20C Dijkstra?](https://codeforces.com/problemset/problem/20/C)：Dijkstra + 路径还原。
- [洛谷 P3366 最小生成树](https://www.luogu.com.cn/problem/P3366)：Kruskal。
- [洛谷 P3387 缩点](https://www.luogu.com.cn/problem/P3387)：强连通分量，阶段二再做。

### DP

- [洛谷 P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：LIS。
- [洛谷 P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)：LCS 转 LIS。
- [洛谷 P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树形 DP。
- [CF 455A Boredom](https://codeforces.com/problemset/problem/455/A)：值域 DP。
- [CF 698A Vacations](https://codeforces.com/problemset/problem/698/A)：状态机 DP。
- [洛谷 P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：树上背包，阶段二再做。

### 字符串

- [洛谷 P3375 KMP 字符串匹配](https://www.luogu.com.cn/problem/P3375)：KMP 模板。
- [洛谷 P4391 无线传输](https://www.luogu.com.cn/problem/P4391)：KMP 周期。
- [洛谷 P3370 字符串哈希](https://www.luogu.com.cn/problem/P3370)：已通过，可 15 分钟校准。
- [洛谷 P3538 OKR-Periods of Words](https://www.luogu.com.cn/problem/P3538)：KMP 周期，挑战题。

### 数论与组合

- [洛谷 P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：逆元。
- [洛谷 P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)：已通过，可 20 分钟校准。
- [洛谷 P1495 中国剩余定理](https://www.luogu.com.cn/problem/P1495)：CRT。
- [洛谷 P3807 卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：组合数取模。
- [CF 550C Divisibility by Eight](https://codeforces.com/problemset/problem/550/C)：数位枚举。

## 6. 每日训练格式

每天建议 2.5~4 小时。如果当天课业很重，最低保底 1 小时。

推荐结构：

- 10 分钟：复习昨天错题记录。
- 90~150 分钟：做新题。
- 30~60 分钟：补题。
- 10 分钟：写日志。

日志格式：

```text
日期：
题目：
耗时：
是否独立 AC：
第一次错误原因：
核心模型：
下次遇到同类题的判断信号：
```

## 7. CF 参赛策略

第一次 CF 不要追求“像老选手一样打”。你现在需要建立流程。

比赛中：

- 前 5 分钟扫 A、B、C 的题面和样例。
- A 题超过 20 分钟仍没过，立刻冷静重读，不要连续乱交。
- B 题超过 35 分钟没有完整思路，先看 C 是否更顺手。
- 每次 WA 后先造 3 个小样例，不要马上改一行再交。

赛后：

- A/B/C 必补。
- D 可先读题解，目标是积累题型，不必当天硬 AC。
- 把错因写进 `dev-history/` 或本计划后续日志。

## 8. 题目来源与链接

洛谷题目链接格式：

- `https://www.luogu.com.cn/problem/P2249`
- 把题号替换即可访问对应题目。

Codeforces 题目链接格式：

- `https://codeforces.com/problemset/problem/4/A`
- `https://codeforces.com/problemset/problem/71/A`

Codeforces 比赛链接：

- `https://codeforces.com/contests/2247`

## 9. 后续维护方式

每周五更新一次本文件，追加：

- 本周完成情况。
- 下周题单。
- 新暴露的薄弱点。
- 是否需要降低/提高题目难度。

如果连续两天无法完成计划，不要补双倍题量。直接砍掉低优先级题，保留：

1. CF/VP。
2. 当周专题核心题。
3. 错题复盘。

这不是偷懒，是控制训练系统不崩。竞赛训练最怕的不是慢，而是三天猛刷、四天失联。
