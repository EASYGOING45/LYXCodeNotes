/*
牛牛有一棵二叉树，该二叉树节点的权值为0/1.
牛牛给你这棵二叉树，想让你告诉他该二叉树从根节点到叶子节点的所有路径中，节点权值为1的个数比权值为0的个数多1的路径有多少条呢。 返回路径数目
*/

/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 返回节点权值1个数比0的个数多一的路径数
     * @param root TreeNode类 权值为0和1的二叉树根节点
     * @return int整型
     */
    // 二叉树 深度优先/广度优先 路径问题选取深度优先
    void dfs(TreeNode* node,int ones,int zeros,int &count)
    {
        if (node == nullptr) {
            return;
        }
        ones += node->val;
        zeros += (1 - node->val);
        
        if (node->left == nullptr && node->right == nullptr) {
            if (ones == zeros + 1) {
                count++;
            }
            return;
        }
        
        dfs(node->left, ones, zeros, count);
        dfs(node->right, ones, zeros, count);
    }
    
    int pathNumber(TreeNode* root) {
        // write code here
        int count = 0;
        dfs(root, 0, 0, count);
        return count;
    }
};