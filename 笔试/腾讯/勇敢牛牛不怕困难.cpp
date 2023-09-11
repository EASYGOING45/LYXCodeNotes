/*
你好，使用C++解决一道算法题，使用ACM模式：
有n个怪物，第i个怪物的战斗力为ai，初始时，牛牛的战斗力为0.
牛牛要与这n个怪物战斗，设牛牛与第i个怪物战斗时牛牛的战斗力为x，则：
1、若x<ai，则牛牛触发被动技能“用改牛牛不怕困难”，使得自己的战斗力提升至ai并战胜这个怪物，这会让牛牛的勇气值提升ai-x
2、若x>=ai，则牛牛会直接战胜这个怪物，并且本次战斗结束后，牛牛的战斗力会降低至ai
牛牛可以任意决定与怪物战斗的顺序，牛牛想知道打败完所有的n只怪物之后，牛牛累计提升的勇气值最大可能是多少。

第一行输入一个整数n
第二行输入n个整数 a1,a2,a3,....,ai

输出一个整数表示牛牛可以得到得最大勇气值
*/

//经典模拟题目

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> monsters(n);
    for (int i = 0; i < n; i++) {
        cin >> monsters[i];
    }

    sort(monsters.begin(), monsters.end(), greater<int>());

    int courage = 0;
    int power = 0;
    for (int i = 0; i < n; i++) {
        if (power < monsters[i]) {
            courage += monsters[i] - power;
            power = monsters[i];
        }
        power--;
    }

    cout << courage << endl;

    return 0;
}