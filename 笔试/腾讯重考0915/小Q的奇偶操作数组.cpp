/*
使用C++，在ACM模式下解决一道算法题：
小Q有一个长度为n的数组，它对这个数组有k次操作机会，操作如下：
可以选择数组中的任意一个数字并改变它
1、如果选择的数字x是奇数，那么这个奇数乘以2，即x=x*2
2、如果选择的数字x是偶数，那么这个偶数乘以2再加1，即x=x*2+1
小Q想让这k次操作之后，数组元素之和最小，请你输出这个最小值是多少？
保证最终的元素之和不超过10的18次方

输入描述：
第一行输入两个正整数n和k，用空格隔开
第二行输入n哥正整数ai，代表数组的每个元素

输出一个整数，代表k次操作之后，数组元素之和的最小值

给出完整的C++代码
*/

//用例通过率为25%
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    sort(arr, arr + n);
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 1 && k > 0) {
            arr[i] *= 2;
            k--;
        } else if (arr[i] % 2 == 0 && k > 0) {
            arr[i] = arr[i] * 2 + 1;
            k--;
        }
    }
    
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    cout << sum << endl;
    
    return 0;
}