/*
有两只猫咪和n条不同类型的鱼，每条鱼都只能被其中一只猫咪吃掉。
下标为i处的鱼被吃掉的得分为：
如果第一只猫咪吃掉，则得分为reward1[i]
如果第二只猫咪吃掉，则得分为reward2[i]
给你一个正整数数组reward1，一个正整数数组reward2，和一个非负整数k，请你返回第一只猫咪恰好吃掉K条鱼的情况下，最大得分为多少？
*/

#include <iostream>
#include <vector>
#include <algorithm>

/*
在 maxScore 方法中，我们使用动态规划的思想来解决问题。我们创建一个二维数组 dp，其中 dp[i][j] 表示第一只猫咪恰好吃掉 i 条鱼时，前 j 条鱼的最大得分。

我们使用两个嵌套的循环来填充 dp 数组。外层循环遍历 i，表示第一只猫咪吃掉的鱼的数量，内层循环遍历 j，表示当前考虑的鱼的下标。对于每个位置 (i, j)，我们有两种选择：要么第一只猫咪吃掉当前的鱼，得分为 reward1[j-1]，要么不吃掉当前的鱼，得分为 dp[i][j-1]。我们选择其中得分较大的情况作为当前位置的最大得分。

最后，返回 dp[k][n]，即第一只猫咪恰好吃掉 k 条鱼时的最大得分。
*/

int maxScoreFunc(std::vector<int>& reward1, std::vector<int>& reward2, int k) {
    int n = reward1.size();
    std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = std::max(dp[i][j-1] + reward1[j-1], dp[i-1][j-1] + reward2[j-1]);
        }
    }
    
    return dp[k][n];
}

int main() {
    std::vector<int> reward1;
    std::vector<int> reward2;
    int k;
    
    int num;
    while (std::cin >> num) {
        reward1.push_back(num);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    
    while (std::cin >> num) {
        reward2.push_back(num);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    
    //std::cout << "请输入猫咪吃掉的鱼的数量k：";
    std::cin >> k;
    
    int maxScore = maxScoreFunc(reward1, reward2, k);
    std::cout<<maxScore<<std::endl;
    //std::cout << "第一只猫咪恰好吃掉" << k << "条鱼的情况下，最大得分为：" << maxScore << std::endl;
    
    return 0;
}