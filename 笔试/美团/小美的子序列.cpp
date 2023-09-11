/*
小美在n行m列的本子上写了许多字母，她会在每一行中找出一个字母，然后组成一个字符串。
小美想指导，组成的字符串中是否存在至少一个字符串包含"meituan"子序列
第一行输入2个整数n，m
接下来n行，每行输入一个长度为m的字符串表示小美写下的字母
若存在至少一个字符串包含"meituan"子序列，则输出”YES“，否则输出”NO“
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool teestStringContain(vector<string>& letters, int n, int m) {
    string target = "meituan";
    
    for (int i = 0; i < n; i++) {
        string current = letters[i];
        int targetIndex = 0;
        
        for (int j = 0; j < m; j++) {
            if (current[j] == target[targetIndex]) {
                targetIndex++;
                
                if (targetIndex == target.length()) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<string> letters(n);
    for (int i = 0; i < n; i++) {
        cin >> letters[i];
    }
    
    if (teestStringContain(letters, n, m)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}