/*
小美的升序数组，给定一个大小为n的数组a，请你判断一个数组是否满足以下条件：
1、数组严格升序，即a1<a2<...<an
2、对于1≤i小于等于n-1，我们定义bi=a(i+1)-ai,则数组b严格降序
第一行输入一个正整数n，代表数组的大小，第二行输入n个正整数ai，代表给定的数组
若满足给定的两个条件，则输出YES，否则输出NO，给出C++代码解决上述问题
*/

#include <iostream>
#include <vector>


using namespace std;

//数组判断
//原数组a[]为严格升序数组 a1<a2<a..an
//bi=a(i+1)-ai  b[]为严格降序数组

bool checkArray(vector<int>& a) {
    int n = a.size();
    
    // 判断数组a是否严格升序
    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i-1]) {
            return false;
        }
    }
    
    // 判断数组b是否严格降序
    vector<int> b(n-1);
    for (int i = 0; i < n-1; i++) {
        b[i] = a[i+1] - a[i];
    }
    
    for (int i = 1; i < n-1; i++) {
        if (b[i] >= b[i-1]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    //原来是要强调输出的YES和NO的大小写问题
    if (checkArray(a)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}