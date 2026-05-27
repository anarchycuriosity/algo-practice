#include <iostream>
using namespace std;
//要点1：压缩/拆分棋盘，我们必须把二维棋盘拆到两个一维数组，尤其是主对角线和反对角线的判断 
//要点2：理解递归，“如果递归回来之后应该怎么处置？”
//要点3：递归终点，一行行顺序种下去，种到n+1才是结束
//要点4：坐标偏移 
#define ll long long 
const int maxn = 1001;
//你甚至不需要一个完整的棋盘
//每次按行移动你只需要一个col数组随时变化
//我只关心同列（因为一行行种下去的所以同行只种一个这是可以保证的） 
//两个对角线，所以我只需要3个一维数组分别表示他们
int col[maxn],md[maxn],ad[maxn];
int ans[maxn];
int n;
int cnt = 0;
//我们会把一个递归塞到for循环里面，这个for循环就一直从r =1 往下走
//循环用的i是列号，每层递归的r是行号
//在i = 1234处都各自展开递归，触底cnt++回来，不触底就提前回来 
void dfs(int r)
{
	if(r > n)//触底，这是最关键的部分但它不应该马上进入，而是作为可选项
	//否则进入递归之后这就没有机会发生了 
	{

		if(cnt <= 2)
		{
			for(int i = 1;i <= n;i++)
			{
				cout << ans[i] << " ";
			}
			cout << "\n";
		}
		
		cnt++;
		return;
	}
	
	
	//这是最大局的部分，你可以从这里纵观整个棋盘 
	for(int i = 1;i <= n;i++)//i是列号 
	{
		if(!col[i]&&!md[i - r + n]&&!ad[i+r])
		{
			col[i] = md[i-r+n] = ad[i +r] = 1;
			ans[r] = i;//这也是列号
			dfs(r+1);
			//递归回来之后怎么办,清除标记 
			col[i] = md[i-r+n] = ad[i+r] = 0;
		}
		
	}
	
}
int main()
{
	cin >> n;
	dfs(1);
	cout << cnt;
	
 } 
