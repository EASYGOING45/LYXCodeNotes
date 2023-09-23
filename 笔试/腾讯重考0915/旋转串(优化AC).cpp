#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

/*
在这个优化版本中，我们将每个字符串的旋转串都生成并加入到哈希表中，然后对每个字符串的所有旋转进行检查。这样，我们避免了生成所有旋转串的开销，同时仍然可以找到匹配的字符串。
*/

bool hasMatchingStrings(const std::vector<std::string>& strings) {
    std::unordered_set<std::string> rotationStrings;
    
    for (const std::string& s : strings) {
        for (int i = 0; i < s.length(); i++) {
            std::string rotation = s.substr(i + 1) + s.substr(0, i + 1);
            if (rotationStrings.count(rotation) > 0) {
                return true;
            }
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
