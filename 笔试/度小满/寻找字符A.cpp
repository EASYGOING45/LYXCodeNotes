/*
现在有n哥人坐成一个圈，也就是说第n个人的下一个是第1个人，每个人背上贴了一个大写字母，这个字母可能是A也可能是B，你的任务是从第一个人开始，顺次向后计数，每遇到一个贴着字母A的人就计数一次，第K次计数道A后停止，现在问你总共需要数多少个人才能停止，保证至少有一个人背上贴的是A
输入：第一行输入两个整数n，k 表示共有n个人，计数A的次数为k
第二行为n个大写字母，只能是A或者B，依次表示为每个人背上所贴的字母
输出：输出一个整数表示共需数多少人
*/
#include <iostream>
#include <vector>
using namespace std;

int countPeople(int n, int k, vector<char>& letters) {
    int count = 0;
    int i = 0;
    while (k > 0) {
        if (letters[i] == 'A') {
            k--;
        }
        count++;
        i = (i + 1) % n;
    }
    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<char> letters(n);
    for (int i = 0; i < n; i++) {
        cin >> letters[i];
    }
    int result = countPeople(n, k, letters);
    cout << result << endl;
    return 0;
}