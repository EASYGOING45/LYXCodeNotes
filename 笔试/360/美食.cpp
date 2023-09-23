/*
小明非常喜欢吃美食，同时他非常讨厌吃到重复的东西。小云为小明准备了n道美食，其中第i道美食的特征值为a: ，因为小明讨厌重复的东西，所以小云想通过混合美食来改变其特征值使得所有美食特征值互不相同。具体的小云每次可以选择两个特征值分别为x,y的美食并将X加入y中变成特征值为X和x+y的美食，现在小云想知道他最少需要混合多少次使得所有美食特征值与不相同。

输入描述：第一行一个正整数n，接下来一行n个数字分别表示每个美食的特征值
输出：输出一个非负整数表示最小混合的次数
给出完整的C++代码
*/
#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> features(n);
    for (int i = 0; i < n; i++) {
        std::cin >> features[i];
    }
    
    std::unordered_set<int> uniqueFeatures;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        while (uniqueFeatures.count(features[i]) > 0) {
            features[i]++;
            count++;
        }
        uniqueFeatures.insert(features[i]);
    }
    
    std::cout << count << std::endl;
    
    return 0;
}