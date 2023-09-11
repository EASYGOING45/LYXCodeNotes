/*
小美有一个数组，她希望删除k个元素，使得剩余的元素两辆之间护卫倍数关系，你能告诉小美有多少种删除方案吗？由于答案过大，请对10的九次方+7取模
第一行输入两个整数n,k 表示数组的长度，删除的元素数量
第二行输入n个整数代表数组a
保证给定的数组中不存在两个相等元素
输出一个整数表示答案
*/

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int countDeletionSchemes(int n, int k, vector<int>& a) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    // Base case: when k = 0, there is only one way to delete 0 elements
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            // If the current element is divisible by the previous element,
            // we have two choices: delete the current element or keep it
            if (a[i] % a[i - 1] == 0) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            }
            // If the current element is not divisible by the previous element,
            // we can only keep the current element
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = countDeletionSchemes(n, k, a);
    cout << ans << endl;

    return 0;
}