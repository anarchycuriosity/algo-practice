// 不管是走 1 步砍一半，还是走 2步砍一半，
// 数字按比例（成倍地）缩小的本质没有变。在计算机科学里，只要规模是成倍缩小的，它的层数就一定是 log n 级别的。
// 总时间复杂度 = 独特状态的总数 * 单次状态转移的代价
// 以这题举例子，假如总共要遍历x个数，最终在记忆数组中存入了3log2 n的数
// 所以，“独特状态的总数”就是指：在整个算法从头到尾运行完的过程中，到底有多少个不同的 x 触发了下面真正的计算逻辑。
// 因为这个算法无论怎么加加减减，它的核心驱动力都是 x / 2。只要是数字不断折半，从 x 缩减到 1
// 独特状态的总数 = 层数（深度） *
// 每一层拥有的状态量(宽度)，不停地指数倍减使得深度是log2n它不是指某一层的数量，而是指整棵递归树上所有不同状态加起来的总和
// 在大 O 表示法中，常数系数 3 是要被忽略的，底数 2
// 也是要被忽略的（因为之间只差一个常数倍数）至于宽度，由于奇数变成偶数，偶数再折半会撞车。在每层中不同的数字最多只有3，这意味着在到达第k层的时候，整个宇宙最多只能有三个数字
// 而单次状态转移的代价，指的就是当x第一次进入函数的时候为了算出他的结果（扣除它调用别的递归函数的时间）要花多少时间。
// 判断和比较都是o(1)，而字符串的拼接的时间取决于字符串的长度，而字符串的长度和递归的层数一致

// 使用unordered_map来快速剪枝，因为数和数之间没有什么联系，用vector索引不过来
// 键值对索引，键就是那个数
// 元素是一个结构体，结构体储存步数和操作
#define ll long long  // 不要有分号，想要改的别名放前面
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
struct Node
{
    int steps;
    std::string ops;
};
// 写一个bool方法比较两个类，返回步数少的和字典序小的，热知识，string直接支持字典序比较
bool is_better(Node& node1, Node& node2)
{
    // 优先比较步数，如果步数一致就比较字典序
    // 所以需要一个判断
    if (node1.steps != node2.steps)
    {
        return node1.steps < node2.steps;
    }
    return node1.ops < node2.ops;
}

std::unordered_map<ll, Node> mem;
Node search(ll x)  // 因为我们是根据当前的数字来遍历，遍历过程中随时可以创建Node类型的变量，所以我们参数只要设置为x即可
{
    if (x == 1)
    {
        return Node{0, ""};  // 结构体的大括号初始化
    }  // 这里是第0层函数，主要是防一手空数据

    // 记忆化的关键就是在开头先查一下能不能查到
    // 这与bfs先找到的一定最短并不一样，而是pk干掉劣解才决定录入，这里并没有类似queue那样的结构
    // 也就是说全局来看，是先递归下去，但是没有触发比较。
    // 先发生小数的比较，小数把结果印到mem，然后返回之后再发生大数的比较，依托着前面撞的小数的结果发生剪枝。
    if (mem.find(x) != mem.end())
    {
        return mem[x];
    }

    Node cur_res;
    if (x % 2 == 0)
    {
        Node pre = search(x >> 1);
        if (x == 2)
        {
            cur_res = Node{pre.steps + 1, pre.ops + "A"};
        }
        else
        {
            cur_res = Node{
                pre.steps + 1,
                pre.ops +
                    "B"};  // 向下，或者说向前（所以是pre）寻找，根据pre的结果在本层拼接，拼接依据是当层的x是不是偶数
        }
    }
    else
    {
        // 如果上一步走的A
        Node pre_a = search(x - 1);  // 正向操作是a，正向+1，反向-1
        Node a_node = Node{pre_a.steps + 1, pre_a.ops + "A"};
        // 如果上一步走的C
        Node pre_c = search(x + 1);
        Node c_node = Node{pre_c.steps + 1, pre_c.ops + "C"};
        // 比较错了！！这会漏掉当前层的节点
        // 对a和c调用search函数的参数是x +-1啊
        //  所以if比较应该要调用a_node或者c_node才对
        //  if (is_better(pre_a, pre_c))
        //  {
        //      cur_res = pre_a;
        //  }
        //  else
        //  {
        //      cur_res = pre_c;
        //  }
        if (is_better(a_node, c_node))
        {
            cur_res = a_node;
        }
        else
        {
            cur_res = c_node;
        }
    }
    // 当层的cur_res在此算完了，因为比较完了以下的分支，所以记录
    // 记录然后返回
    mem[x] = cur_res;
    return cur_res;
}
int main()
{
    int m;
    std::cin >> m;
    std::cout << search(m).steps << "\n";
    std::cout << search(m).ops;
}
