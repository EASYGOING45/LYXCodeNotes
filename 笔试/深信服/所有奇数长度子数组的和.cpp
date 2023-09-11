/*
已知子数组定义为原数组中的一个连续子序列，现给定一个正整数数组arr，请计算该数组内所有可能的奇数长度子数组的数值之和
输入一个正整数数组arr，输出所有可能的奇数长度子数组的和
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
    std::vector<int> arr;
    int num;

    while (std::cin >> num) {
        arr.push_back(num);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    int length = longestDecreasingSubsequence(arr);
    cout<<length<<endl;
    
    return 0;
}