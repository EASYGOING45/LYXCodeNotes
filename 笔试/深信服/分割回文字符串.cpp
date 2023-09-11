/*
解决一道算法题：
给你一个字符串string,string仅由小写英文字母组成，且长度不超过1000，请你讲string分割成一些子串，使每个 子串都是回文，返回符合要求的最少分割次数
*/
class Solution {
public:
    int min_cut_string(string str) {
        int n = str.length();
        
        // 创建一个二维DP表，用于存储从i到j的子串所需的最小分割次数
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 创建一个一维DP表，用于存储从0到i的子串所需的最小分割次数
        vector<int> cuts(n, 0);
        
        // 初始化DP表
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        // 计算所有可能子串的最小分割次数
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                
                if (str[i] == str[j] && (len == 2 || dp[i+1][j-1] == 1)) {
                    dp[i][j] = 1;
                }
            }
        }
        
        // 计算所需的最小分割次数
        for (int i = 0; i < n; i++) {
            int minCuts = i;
            
            for (int j = 0; j <= i; j++) {
                if (dp[j][i] == 1) {
                    minCuts = min(minCuts, (j == 0) ? 0 : cuts[j-1] + 1);
                }
            }
            
            cuts[i] = minCuts;
        }
        
        return cuts[n-1];
    }
};