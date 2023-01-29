# 算法-二叉树Part2

## 102-层序遍历

借助队列

队列先进先出，符合⼀层⼀层遍历的逻辑，⽽是 ⽤栈先进后出适合模拟深度优先遍历也就是递归的逻辑

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        //层序遍历 借助队列 先进先出
        queue<TreeNode*> que;
        if(root!=nullptr)
        {
            que.push(root);
        }
        vector<vector<int>> res;
        while(!que.empty())
        {
            //队列不为空时执行循环体
            int size = que.size();
            vector<int> vec;
            // 使用固定大小的size
            for(int i=0;i<size;i++)
            {
                TreeNode* node=que.front();     //首元素
                que.pop();
                vec.push_back(node->val);
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            res.push_back(vec);
        }
        return res;
    }
};
```

## 199-二叉树的右视图

![image-20230104104435833](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104104435833.png)

```C++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) 
    {
        queue<TreeNode*> que;
        if(root!=nullptr) que.push(root);
        vector<int> res;
        while(!que.empty())
        {
            int size=que.size();
            for(int i=0;i<size;i++)
            {
                TreeNode* node =que.front();
                que.pop();
                if(i==(size-1)) res.push_back(node->val); //将每⼀层的最后元素放⼊result数组中
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return res;
    }
};
```

## 637-二叉树的层平均值

```C++
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) 
    {
        queue<TreeNode*> que;
        vector<double> res;
        if(root!=nullptr) que.push(root);
        while(!que.empty())
        {
            int size = que.size();
            double sum = 0; //计算每一层的结点和
            for(int i=0;i<size;i++)
            {
                TreeNode* cur=que.front();
                que.pop();
                sum+=cur->val;
                if(cur->left) que.push(cur->left);
                if(cur->right) que.push(cur->right);
            }
            res.push_back(sum/size);    //存储均值
        }
        return res;
    }
};
```

## 429-N叉树的层序遍历

https://leetcode.cn/problems/n-ary-tree-level-order-traversal/

![image-20230104105538472](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104105538472.png)

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) 
    {
        queue<Node*> que;
        vector<vector<int>> res;
        if(root!=nullptr) que.push(root);
        while(!que.empty())
        {
            int size=que.size();
            vector<int> vec;
            for(int i=0;i<size;i++)
            {
                Node* cur=que.front();
                que.pop();
                vec.push_back(cur->val);
                for(int i=0;i<cur->children.size();i++)
                {
                    if(cur->children[i]) que.push(cur->children[i]);
                }
            }
            res.push_back(vec);
        }
        return res;
    }
};
```

## 515-在每个树行中找最大值

https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/

![image-20230104105617288](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104105617288.png)

```C++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) 
    {
        queue<TreeNode*> que;
        if(root != nullptr) que.push(root);
        vector<int> res;
        while(!que.empty())
        {
            int size = que.size();
            int maxValue = INT_MIN;
            for(int i=0;i<size;i++)
            {
                TreeNode* node = que.front();
                que.pop();
                maxValue = node->val > maxValue ? node->val : maxValue;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            res.push_back(maxValue);
        }
        return res;
    }
};
```

## 116-填充每个节点的下一个右侧节点指针

https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/

![image-20230104110149965](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104110149965.png)

```C++
class Solution {
public:
    Node* connect(Node* root) 
    {
        queue<Node*> que;
        if(root != nullptr) que.push(root);
        while(!que.empty())
        {
            int size=que.size();
            vector<int> vec;
            Node* nodePre;  //当前层的头结点
            Node* node;
            for(int i=0;i<size;i++)
            {
                if(i==0)
                {
                    nodePre = que.front();  //当前层的头结点
                    que.pop();
                    node=nodePre;
                }
                else
                {
                    node = que.front();
                    que.pop();
                    nodePre->next = node;   //本层前一个结点的next指针指向本节点
                    nodePre = nodePre->next;
                }
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            nodePre->next = NULL;   //每层的最后一个结点指向NULL
        }
        return root;   
    }
};
```

## 117-填充每个节点的下一个右侧指针Ⅱ

![image-20230104110804986](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104110804986.png)

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) 
    {
        queue<Node*> que;
        if(root != NULL)
        {
            que.push(root);
        }
        while(!que.empty())
        {
            int size=que.size();
            vector<int> vec;
            Node* nodePre;  //当前层的头节点
            Node* node;
            for(int i=0;i<size;i++)
            {
                if(i==0)
                {
                    nodePre = que.front();  //取出头节点
                    que.pop();
                    node = nodePre;
                }
                else
                {
                    node=que.front();
                    que.pop();
                    nodePre->next=node;
                    nodePre=nodePre->next;
                }
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            nodePre->next = NULL;
        }
        return root;
    }
};
```

![image-20230104111253972](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230104111253972.png)