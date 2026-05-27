#include <string>
#include <string.h>
#include <iostream>
using namespace std;
//a是被除数，b是除数，c是商，t是常常用来移位的除数
//我们用数组的0位存储有效位数，从1开始存有效值，顺序
const int maxn = 500;
int a[maxn],b[maxn],c[maxn],t[maxn];
string stra = "";
string strb = "";
//我们需要一个函数实现复制并且移位，从b到t
//一个函数比较大小决定是否可以除
//一个函数去做高精度减法
void cpy(int bb[],int tt[],int offset)//把bb数组完全复制到tt数组的基础上移动offset，相当于tt被覆盖 
{
	for(int i = 1;i <= bb[0];i++)
	{
		tt[i + offset] = bb[i];
	}
	tt[0] = bb[0] + offset;
}
bool comp(int aa[],int tt[])//确认是否可以相减,如果不行就得移位了 
{
	if(aa[0] > tt[0])//位数大就win 
	{
		return true;
	}
	if(aa[0] < tt[0]) 
	{
		return false;
	}
	// 这里不要用else if 
	if(aa[0] == tt[0])//只要有一个大就win，否则lose，相等继续 
	{
		for(int i = 1;i <= aa[0];i++)
		{
			if(aa[i] < tt[i])
			{
				return false;
			}
			else if(aa[i] > tt[i])
			{
				return true;
			}
			
		}
	}
	return true;
} 
void sub(int aa[],int tt[])
{
	for(int i = aa[0];i >= 1;i--)
	{

		if(aa[i] < tt[i])
		{
			aa[i]+=10;
			aa[i - 1] -= 1;
		}
		
		aa[i] -= tt[i];
		
	}
}
int main()
{
	cin >> stra >> strb;
	int lena = stra.size();
	int lenb = strb.size();
	a[0] = lena;
	b[0] = lenb;
	for(int i = 1;i <= lena;i++)
	{
		a[i] = stra[i - 1] - '0';
	}
	for(int i = 1;i <= lenb;i++)
	{
		b[i] = strb[i-1] - '0';
	}
	//就像4位数除以二位数，商的有效位数是2一样，我们可以知道商的有效位数
	//有效长度可以理解为数组不为0的末位 
	c[0] = a[0] - b[0] + 1;//因为我们是从1开始的，所以+1

	for(int i = 1;i <= c[0];i++)
	{
		memset(t,0,sizeof(t));
		//我们根据当前的商算到哪一位来决定位移多少
		cpy(b,t,i-1);
		//因为我们comp函数是基于a的有效位来的，所以我们要复制t的值过去
		a[0] = t[0];
		while(comp(a,t) == true)
		{
			sub(a,t);
			c[i]++;
		 }				 
	}
	for(int i = 1;i <= c[0];i++)
	{
		if(c[i] == 0)
		{
			continue;
		}
		cout << c[i];
	}
 } 
