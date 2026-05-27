#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//我们用3个根堆，正2个，负1一个来插入
//为什么是插入而不是交换呢，因为如果说正数都是一样的就会重复换很多次一样的，这没有意义
//然后其实可以想到最难处理的也就是特例其实就是一样的数
//只有可能在交界的位置出现为0的情况，所以插正数插负数都是一样的
//并不需要真的插入，在两个数组进行操作即可，可惜赛时没有想到拆开它而是用序列去标记
//赛时只想到交换了
//仔细详细交换这个思路其实完全就是错的，因为如果最大和最小的进行交换都会为0那中间的数不都一样了嘛
int main()
{
	int tmp;
	priority_queue<int,vector<int>,greater<int>> pq_min_p;
	priority_queue<int> pq_max_p;//负数，默认是大根堆
	priority_queue<int> pq_max_m;//负数，默认是大根堆
	int n;
	cin >> n;
	if(n == 0)//防御性编程防RE 
	{
		cout << "YES";
		return 0;
	}
	while(n--)
	{
		cin >> tmp;
		if(tmp ==0)
		{
			cout << "No";
			return 0;
		}
		else if(tmp > 0)
		{
			pq_max_p.push(tmp);
			pq_min_p.push(tmp);  
		}
		else
		{
			pq_max_m.push(tmp); 
		}
	 }
	 if(pq_min_p.empty() || pq_max_p.empty())
	 {
	 	cout << "YES";
	 	return 0;
	 }
	 if(pq_min_p.top() + pq_max_m.top() ==0)
	 {
	 	if(pq_max_p.top() + pq_max_m.top() == 0)
		 {
		 	cout << "No";
		 	return 0;
		  } 
	  } 
	  cout << "YES";
 } 
