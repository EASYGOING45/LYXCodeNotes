/*
接下来做下一道题，小美有很多的彩虹糖，每颗彩虹糖都有一个颜色，她每天可以吃两颗彩虹糖，如果今天吃的彩虹糖组合是之前没吃过的组合，则小美今天会很高兴
例如，小美有6颗彩虹糖，颜色分别是[1,1,4,5,1,4]
小红第一天吃一组颜色为1和4得到彩虹糖，小美会很高兴
第二天吃一组颜色为4和1的彩虹糖，小美不会很高兴
第三天吃一组颜色为1和5的彩虹糖，小美会很高兴，此时小美共有两条会很高兴
小美想知道，她最多有几天会很高兴
第一行输入一个整数n，表示彩虹糖数量
第二行输入n个整数表示彩虹糖颜色a
给出C++代码
*/

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

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int maxHappyDays(int n, vector<int>& a) {
    unordered_set<int> combinations;
    int happyDays = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int combination = (1 << a[i]) | (1 << a[j]);
            if (combinations.find(combination) == combinations.end()) {
                combinations.insert(combination);
                happyDays++;
            }
        }
    }

    return happyDays;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = maxHappyDays(n, a);
    cout << ans << endl;

    return 0;
}