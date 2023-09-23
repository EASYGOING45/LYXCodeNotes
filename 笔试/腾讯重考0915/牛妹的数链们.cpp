// 牛妹有一堆数链，这些数链里面的数字都杂乱无章，牛妹想整理一下这些数字，把它们从小到大排成一个数链
// 如 输入 {{1,3,5},{2,4,6},{1,2,3,4,5,6}}
// 输出 {1,1,2,2,3,3,4,4,5,5,6,6}


/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */

class Solution {
public:
    ListNode* solve(vector<ListNode*>& a) {
        // 将所有链表的节点存入一个vector中
        vector<int> nums;
        for (auto node : a) {
            while (node != nullptr) {
                nums.push_back(node->val);
                node = node->next;
            }
        }
        
        // 对vector进行排序
        sort(nums.begin(), nums.end());
        
        // 根据排序后的vector重新构建链表
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        for (int num : nums) {
            curr->next = new ListNode(num);
            curr = curr->next;
        }
        
        return dummy->next;
    }
};