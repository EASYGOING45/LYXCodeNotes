# CATL笔试

## 翻转字符串里的每个单词

- 输入 `the sky is blue`
- 输出 `eth yks si eulb`

```Python
#
# 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
#
# 翻转字符串里的每个单词
# @param words string字符串 一个个单词，以空格分隔，如"the sky is blue"
# @return string字符串
#
class Solution:
    def reverseString(self , words: str) -> str:
        # write code here
        words = words.split(' ')
        # 2. 然后把单词翻转
        words = [word[::-1] for word in words]
        # 3. 最后把单词用空格拼接起来
        return ' '.join(words)
```



```C++
#include <iostream>
#include <vector>
#include <sstream>

class Solution {
public:
    std::string reverseString(std::string words) {
        // 1. 先将字符串按空格分割为单词
        std::vector<std::string> wordsVec;
        std::stringstream ss(words);
        std::string word;
        while (ss >> word) {
            wordsVec.push_back(word);
        }
        
        // 2. 然后把单词翻转
        for (auto& word : wordsVec) {
            std::reverse(word.begin(), word.end());
        }
        
        // 3. 最后把单词用空格拼接起来
        std::string result = wordsVec[0];
        for (int i = 1; i < wordsVec.size(); i++) {
            result += " " + wordsVec[i];
        }
        
        return result;
    }
};

int main() {
    Solution solution;
    std::string words = "the sky is blue";
    std::cout << solution.reverseString(words) << std::endl;
    
    return 0;
}
```

## 栈和排序

给你一个1->n的排列和一个栈，入栈顺序给定

你要在不打乱入栈顺序的情况下，对数组进行从大到小排序

当无法完全排序时，请输出字典序最大的出栈序列

**输入描述:**第一行一个数n，第二行n个数，表示入栈的顺序，用空格隔开，结尾无空格

**输出描述:**输出一行n个数表示答案，用空格隔开，结尾无空格

示例1

输入：

> 输入：
>
> ​	5
> ​		2 1 5 3 4
>
> 输出：
>
> ​	 5  4 3 1 2

```C++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++)
        cin >> v[i];

    vector<int> biggest(n, v[n-1]);
    for(int i = n-2; i >= 0; i--)
        biggest[i] = max(biggest[i+1], v[i]);

    vector<int> ans;
    stack<int> s;

    for(int i = 0; i < n; i++) {
        s.push(v[i]);
        while(!s.empty() && s.top() > biggest[i+1]) {
            ans.push_back(s.top());
            s.pop();
        }
    }
    while(!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }
    for(auto &num : ans)
        cout << num << " ";
    cout << endl;
    return 0; 
}
```

## 牛牛的数组匹配

![image-20230802140304484](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230802140304484.png)

```C++
#include<iostream>
#include<stdlib.h>
#include<math.h>

using namespace std;
    //        存放子数组的和，以及左右下标
struct person{
    int left,  right;
    int sum_b = 0;
};
int main()
{    
    int* a, * b;
    //    创建结构体变量
    person sum[2000];
    int n, m, i, j;
    int sum_a = 0, d = 0;
    cin >> n >> m;
    a = (int*)malloc(n * 4);
    b = (int*)malloc(m * 4);
    for (i = 1; i <= m; i++)
        d += i;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        sum_a += a[i];
    }
    for (i = 0; i < m; i++)
        cin >> b[i];
    //        初始化
    sum[0].left = 0, sum[0].right = 0;
    //        求和
    for (i = 0; i < d; i++)
    {
        for (j = sum[i].left; j <= sum[i].right; j++)
            sum[i].sum_b += b[j];
        sum[i].sum_b = abs(sum[i].sum_b - sum_a);
            //    左右下标判断
            if (sum[i].right == m - 1)
            {
                sum[i + 1].left = sum[i].left + 1;
                sum[i+1].right = sum[i + 1].left;
            }
            else
            {
                sum[i + 1].left = sum[i].left;
                sum[i+1].right=sum[i].right+1;
            }
    }
        //        判断输出
    sum[d].left = sum[0].left;
    sum[d].right = sum[0].right;
    sum[d].sum_b = sum[0].sum_b;
    for(i=1;i<d;i++)
        if (sum[d].sum_b > sum[i].sum_b)
        {
            sum[d].left = sum[i].left;
            sum[d].right = sum[i].right;
            sum[d].sum_b = sum[i].sum_b;
        }
    for (i = sum[d].left; i <= sum[d].right; i++)
        cout << b[i] << ' ';
    cout << endl;
    system("pause");
    return 0;
}
```



```Python
n=[int(i) for i in input().split()]
a=[int(i) for i in input().split()]
b=[int(i) for i in input().split()]

s=sum(a)

min=abs(sum(b)-s)
idx=[0,n[1]]
for i in range(0,n[1]):
    for j in range(i+1,n[1]+1):
        if abs(sum(b[i:j])-s)<min:
            min=abs(sum(b[i:j])-s)
            idx[0]=i
            idx[1]=j
print(' '.join(str(i) for i in b[idx[0]:idx[1]]))

```

