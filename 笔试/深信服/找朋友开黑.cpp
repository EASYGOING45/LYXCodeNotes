/*
解决一道算法题：
小张是一个游戏高手，想要在游戏中组建一个工会。小张有n个游戏好友，每个好友都愿意和他一起组工会，每个好友都有自己的游戏等级和与对小张的好感度，小张希望组建完工会后，所有人对自己的总好感度最大，如果在工会中有某个好友比另外的好友高至少d个等级，那么等级低的好友会感到自己的游戏水平菜，就不会对小张有好感度，请帮助他找到最佳的游戏队友
输入描述：
第一行输入包含两个整数n和d，分别是小张的朋友数量和感到游戏等级低的最小差异
接下来n行是校长的朋友的信息，第(i+1)行包含第i个朋友的信息mi，si，分别是游戏等级和好感度
输出好友对小张的总好感度
给出完整的C++代码作答
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Friend {
    int level;
    int like;
};

bool compareFriends(const Friend& a, const Friend& b) {
    return a.level < b.level;
}

int main() {
    int n, d;
    cin >> n >> d;

    vector<Friend> friends(n);
    for (int i = 0; i < n; i++) {
        cin >> friends[i].level >> friends[i].like;
    }

    sort(friends.begin(), friends.end(), compareFriends);

    int maxLike = 0;
    int currentLike = 0;
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (friends[i].level - friends[j].level >= d) {
            currentLike -= friends[j].like;
            j++;
        }
        currentLike += friends[i].like;
        maxLike = max(maxLike, currentLike);
    }

    cout << maxLike << endl;

    return 0;
}