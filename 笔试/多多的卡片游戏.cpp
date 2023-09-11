#include <iostream>
using namespace std;

// 多多同学最近参与了一个卡片游戏，规则如下
//  有N张卡片，第i张卡片上写着整数X_i，玩家必须使用这N张卡片创建尽可能多的卡片对
//  满足以下其中一个条件的两张卡片，即为卡片对：
//  （1）两张卡片上的整数相同
//  （2）两张卡片上的整数之和是M的倍数
//  请帮多多同学找出可以创建的最大卡片对数，请注意，一张卡片不能用于多个卡片对
//  第一行输入包含一个正整数T，表示接下来共有T组测试用例
//  输出每组测试用例打印出可创建卡片对的最大值

// 思路：将卡片上的数字对M取余，余数相同的卡片可以组成一对，余数为0的卡片可以组成一对，余数为M/2的卡片可以组成一对
// 通过率 100%
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int m;
		cin >> m;
		int *a = new int[m];
		for (int i = 0; i < m; i++)
			a[i] = 0;
		int num;
		cin >> num;
		int max = 0;
		for (int i = 0; i < num; i++)
		{
			int temp;
			cin >> temp;
			a[temp % m]++;
			if (temp % m == 0)
				max++;
		}
		if (m % 2 == 0 && a[m / 2] != 0)
			max++;
		for (int i = 1; i < m / 2; i++)
		{
			if (a[i] != 0 && a[m - i] != 0)
			{
				if (a[i] > a[m - i])
					max += a[m - i];
				else
					max += a[i];
			}
		}
		cout << max << endl;
		delete[] a;
	}
	return 0;
}