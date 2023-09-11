#include <iostream>
using namespace std;

// 多多最近很喜欢回文字符串，回文字符串指的是从前读和从后读都相同的字符串，例如"p","dpd","pdp","pddp"都是回文字符串，"pdd"则不是
// 现在有一个仅由小写字母组成的字符串S，想知道对其中的字符进行K次修改后（每次修改前后字符不一样），新生成的字符串是否可以是回文字符串
// 第一行输入一个正整数T，代表测试数据的组数
// 对于每组测试数据，分别有两行：第一行有一个字符串S，表示初始字符串，第二行有一个正整数K，表示修改次数
// 对于每组测试数据，如果字符串S经过K次修改后，可以变成回文字符串，那么输出一行YES，否则输出一行NO

// 思路：将字符串分为两部分，分别从两端开始比较，如果有不同的字符，则将其修改为相同，修改次数减一，如果修改次数为负，则输出NO
// 如果修改次数为0，但是字符串还有不同的字符，也输出NO，否则输出YES

// 通过率 85%
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string str;
		int k;
		cin >> str >> k;
		int i = 0, j = str.size() - 1;
		while (i < j)
		{
			if (str[i] != str[j])
			{
				str[i] = str[j];
				k--;
			}
			i++;
			j--;
		}
		if (k < 0)
			cout << "NO" << endl;
		else if (k == 0 && i != j)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	}
	return 0;
}