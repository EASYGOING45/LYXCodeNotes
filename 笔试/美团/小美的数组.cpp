/*
很好，接下来做下一道题：
小美拿到了一个数组，她每次可以进行如下操作之一：
1、选择一个元素，使其乘以2
2、选择一个元素，使其除以2，向下取整
小美希望第一个元素变成所有元素的最大值，请你判断小美最少需要操作多少次？
第一行输入一个正整数n，代表数组的大小
第二行输入n个正整数ai，代表小美拿到的数组
输出最小操作次数

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minOperations(vector<int>& nums) {
    int n = nums.size();
    int maxNum = *max_element(nums.begin(), nums.end());
    int minOperations = 0;
    
    while (maxNum > nums[0]) {
        if (maxNum % 2 == 0) {
            maxNum /= 2;
        } else {
            maxNum--;
        }
        minOperations++;
    }
    
    return minOperations;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int minOps = minOperations(nums);
    cout << minOps << endl;
    
    return 0;
}