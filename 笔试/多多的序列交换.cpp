#include <iostream>
using namespace std;

// 多多有两个长度为n的数字序列，a1,a2,...,an和b1,b2,...,bn，多多可以将任意的ai与bi交换，多多现在想知道最少需要交换多少次能使得一个多项式最大，请你告诉多多
// 第一行输入一个整数T，表示接下来共有T组数据，每组数据第一行一个整数n
// 第二行n个整数a1....an，第三行n个整数，b1....bn
// 对于每组数据，输出一个数，表示最少需要的交换次数

// 思路：将a数组和b数组从大到小排列，然后将a数组中的最大值和b数组中的最大值交换，这样就能得到最大的多项式，交换次数就是a数组中最大值的下标
// 通过率 100%
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int num;
		cin >> num;
		int *a = new int[num];
		int *b = new int[num];
		for (int i = 0; i < num; i++)
			cin >> a[i];
		for (int i = 0; i < num; i++)
			cin >> b[i];
		int maxa = a[0], maxb = b[0], maxai = 0, maxbi = 0;
		for (int i = 0; i < num; i++)
		{
			if (a[i] > maxa)
			{
				maxa = a[i];
				maxai = i;
			}
			if (b[i] > maxb)
			{
				maxb = b[i];
				maxbi = i;
			}
		}
		int temp = a[maxai];
		a[maxai] = b[maxbi];
		b[maxbi] = temp;
		int sum = 0;
		for (int i = 0; i < num; i++)
			sum += a[i];
		cout << sum << endl;
		delete[] a;
		delete[] b;
	}
	return 0;
}