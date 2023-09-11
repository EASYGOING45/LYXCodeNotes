/*
你想对一棵奇怪的二叉树进行运算，这棵树每个节点要么有两个子节点，要么没有子节点，如果一个节点没有子节点，则这个节点的值为1，如果某个节点有两个子节点，这个节点的值就是它的两个子节点的值做某种运算后的结果，某种运算取决于这个节点的颜色，如果为红色则为乘法，如果为蓝色则是加法
你想知道根节点的值
树，是一种无向无环联通图
输入：第一行一个正整数n表示节点个数
第二行n-1个正整数p[2,3,...n] p[i]表示第i个节点的父节点，1号节点是根节点
第三行n个整数c[1,2,....n]当c[i]=1时表示第i个节点是 蓝色，c[i]=2则表示红色
输出一行一个整数表示根节点的值
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    vector<Node*> children;
};

int calculate(Node* node) {
    if (node->children.empty()) {
        return 1;
    }
    
    int result = 0;
    if (node->value == 1) {
        result = 0;
        for (Node* child : node->children) {
            result += calculate(child);
        }
    } else if (node->value == 2) {
        result = 1;
        for (Node* child : node->children) {
            result *= calculate(child);
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    vector<Node*> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node();
    }
    
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        nodes[parent - 1]->children.push_back(nodes[i]);
    }
    
    for (int i = 0; i < n; i++) {
        cin >> nodes[i]->value;
    }
    
    int rootValue = calculate(nodes[0]);
    cout << rootValue << endl;
    
    return 0;
}