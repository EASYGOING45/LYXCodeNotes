/*
对于一个字符串，如果把字符串的第一个字符放到最后，得到的新串就是原来字符串的旋转串。
一个字符串的旋转串的旋转串也是这个字符串的旋转串，即这种关系具有传递性
例如：abc的旋转串有：bca cab abc
如果存在一个字符串，既是x的旋转串也是y的旋转串，那么我们称x，y匹配
请回答一系列字符串中是否有两个字符串匹配

输入描述：
第一行输入一个正整数T，表示输入的数据的组数
每组数据第一行为一个整数n
接下来n行，每行输入一个只含小写字母的字符串s

每个字符串的长度都相同且不会超过50

如果存在两个字符串匹配，则输出YES，否则输出NO
*/
// 哈希表优化版本 用例通过率为86.67%
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

bool hasMatchingStrings(const std::vector<std::string>& strings) {
    std::unordered_set<std::string> rotationStrings;
    
    for (const std::string& s : strings) {
        std::string rotation = s.substr(1) + s[0];
        if (rotationStrings.count(rotation) > 0) {
            return true;
        }
        rotationStrings.insert(s);
    }
    
    return false;
}

int main() {
    int T;
    std::cin >> T;
    
    while (T--) {
        int n;
        std::cin >> n;
        
        std::vector<std::string> strings(n);
        for (int i = 0; i < n; i++) {
            std::cin >> strings[i];
        }
        
        if (hasMatchingStrings(strings)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
    
    return 0;
}