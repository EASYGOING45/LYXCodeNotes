/*
牛妹有一个序列a1,a2,a3,.....,an，牛妹可以执行k次操作，每次操作步骤如下：
1、牛妹选择一个pos （1<=pos<=n)
2、将apos在二进制下最低为的1变成0
牛妹想知道k次操作后序列之和的最小值为多少？

输入描述：
第一行输入两个正整数 n，k
接下来输入n个正整数，表示牛妹的序列

输出一个数，表示k次操作之后序列之和的最小值
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    // 计算每个数最低位的1所在的位置
    vector<int> lowestOnePos(n);
    for (int i = 0; i < n; i++)
    {
        lowestOnePos[i] = __builtin_ffs(nums[i]);
    }

    // 排序 lowestOnePos 数组
    sort(lowestOnePos.begin(), lowestOnePos.end());

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        // 如果 k 大于 0，并且当前位置的最低位为1
        if (k > 0 && (lowestOnePos[i] != 0))
        {
            sum += (nums[i] - (1 << (lowestOnePos[i] - 1))); // 将最低位的1变为0
            k--;                                             // 操作次数减1
        }
        else
        {
            sum += nums[i];
        }
    }

    cout << min(sum, *min_element(nums.begin(), nums.end())) << endl;

    return 0;
}
