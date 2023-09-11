#include <iostream>
#include <vector>
using namespace std;

// 计算小球摆放方案的个数
int countBallArrangements(int N)
{
    // 创建一个动态规划数组dp，dp[i]表示i个小球的摆放方案个数
    std::vector<int> dp(N + 1, 0);

    // 初始化边界条件
    dp[0] = 1;
    dp[1] = 2;

    // 计算dp数组的值
    for (int i = 2; i <= N; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[N];
}

int main()
{
    int N;
    // std::cout << "请输入小球的个数N：";
    std::cin >> N;

    int arrangements = countBallArrangements(N);
    cout << arrangements << endl;
    // std::cout << "小球摆放方案的个数为：" << arrangements << std::endl;

    return 0;
}