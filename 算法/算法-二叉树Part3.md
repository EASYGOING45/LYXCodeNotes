# 算法-二叉树Part3

## 226-翻转二叉树

![image-20230121110052995](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230121110052995.png)

```C++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        //前序遍历法
        //递归交换每个节点的左右孩子
        if(root == nullptr)
        {
            return root;
        }
        swap(root->left,root->right);   //交换
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```

```C++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        //迭代法 
        if(root == nullptr)
        {
            return root;
        }
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty())
        {
            TreeNode* node = st.top();    //中间
            st.pop();
            swap(node->left,node->right);
            if(node->right) st.push(node->right);
            if(node->left) st.push(node->left);
        }
        return root;
    }
};
```

## 101-对称二叉树

![image-20230121110616718](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230121110616718.png)

```C++
class Solution {
public:
    bool compare(TreeNode* left,TreeNode* right)
    {
        //排除空节点情况
        if(left == nullptr && right != nullptr) return false;
        else if(left != nullptr && right==nullptr) return false;
        else if(left==nullptr && right==nullptr) return true;

        //数值不同的情况
        else if(left->val != right->val) return false;

        //左右节点都不为空，且数值相同的情况 此时递归
        bool outside = compare(left->left,right->right); //左子树：左 ?= 右子树：右
        bool inside = compare(left->right, right->left); // 左子树：右、 右子树：左
        bool isSame = outside && inside; // 左子树：中、 右子树：中 （逻辑处理）
        return isSame;
    }
    bool isSymmetric(TreeNode* root) 
    {
        if(root == nullptr) return true;
        return compare(root->left,root->right);
    }
};
```

