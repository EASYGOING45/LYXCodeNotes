/*
使用C++，在ACM模式下解决一道算法题：删除中位数问题
牛牛有一个长度为n的序列a，以及一个长度为n-1的序列b，序列b中的元素不重复。
对于这个序列a，牛牛会先求出他的中位数，然后再根据序列b的顺序依次删除原序列a中对应下标的元素，即删除a[b[i]],0<=i<=n-1
每次删完一个数后，牛牛会统计序列a中剩下的数的中位数是什么，若剩下的数为奇数，牛牛会取中间数（排序后），若为偶数，牛牛回取中间两个数的平均值（排序后）
牛牛把每次的结果都记录下来了，但是他怕出错，给你初始的序列a和b，希望你能帮他验证以下。

输入描述：
第一行输入t，表示有t组数据
接下来有3 * t行，每组数据的第一行为n，表示序列长度
第二行为n个整数，表示序列a的元素
第三行为n-1个整数，表示序列b的元素

输出为t行，每行有n个整数，表示每组数据的答案，其中输出若是浮点数保留小数点后一位，否则按整数输出
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

double calculateMedian(vector<int>& a) {
    int n = a.size();
    sort(a.begin(), a.end());
    if (n % 2 == 1) {
        return a[n/2];
    } else {
        return (a[n/2 - 1] + a[n/2]) / 2.0;
    }
}

void solve() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        vector<int> b(n-1);
        for (int i = 0; i < n-1; i++) {
            cin >> b[i];
        }
        
        vector<double> results;
        results.push_back(calculateMedian(a));
        
        for (int i = 0; i < n-1; i++) {
            a.erase(a.begin() + b[i] - i - 1);
            results.push_back(calculateMedian(a));
        }
        
        for (int i = 0; i < n; i++) {
            if (results[i] == (int)results[i]) {
                cout << (int)results[i] << " ";
            } else {
                cout << fixed << setprecision(1) << results[i] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    solve();
    return 0;
}