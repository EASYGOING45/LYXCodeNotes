/*
解决一道算法题：
给定一个未经排序的整数数组，找到最长且连续递减的子序列，并返回该序列的长度。
连续递减的子序列可以由两个下标l和r确定(l<r)，如果对于每个l<=i<r,都有nums[i]<nums[i+1]，那么子序列[nums[l],nums[l+1],...nums[r-1],nums[r]]就是连续递减子序列，
输入一个未经排序的整数数组
输出连续递减子序列的长度
例如：
输入 7 4 5 3 1
输出 3
*/
#include <iostream>
#include <vector>
using namespace std;

int longestDecreasingSubsequence(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    
    int maxLength = 1;
    int currentLength = 1;
    
    for (int i = 1; i < n; i++) {
        if (nums[i] < nums[i-1]) {
            currentLength++;
        } else {
            maxLength = max(maxLength, currentLength);
            currentLength = 1;
        }
    }
    
    maxLength = max(maxLength, currentLength);
    
    return maxLength;
}

int main() {
    vector<int> nums = {7, 4, 5, 3, 1};
    int length = longestDecreasingSubsequence(nums);
   cout<<length<<endl;
    
    return 0;
}