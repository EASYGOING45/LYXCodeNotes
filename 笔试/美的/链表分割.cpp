/*
解决一道算法题
请设计一个函数，函数可以将一个链表分成两个子链表，前半部分一个，后半部分一个，对于奇数个数的链表，则额外的元素在前面的子链表
样例输入:
{1,2,3,4,5}
输出: [{1,2,3},{4,5}]
*/

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

std::pair<ListNode*, ListNode*> splitList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return {head, nullptr};
    }
    
    ListNode* slow = head;
    ListNode* fast = head->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    ListNode* secondHead = slow->next;
    slow->next = nullptr;
    
    return {head, secondHead};
}

ListNode* createLinkedList(const std::vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    
    for (int num : nums) {
        curr->next = new ListNode(num);
        curr = curr->next;
    }
    
    return dummy->next;
}

void printLinkedList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr) {
            std::cout << ",";
        }
        head = head->next;
    }
}

int main() {
    //std::cout << "请输入链表元素，以空格分隔：" << std::endl;
    std::vector<int> nums;
    int num;
    
    while (std::cin >> num) {
        nums.push_back(num);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    
    ListNode* head = createLinkedList(nums);
    
    std::pair<ListNode*, ListNode*> result = splitList(head);
    ListNode* firstHead = result.first;
    ListNode* secondHead = result.second;
    
    std::cout << "[";
    printLinkedList(firstHead);
    std::cout << "],[";
    printLinkedList(secondHead);
    std::cout << "]" << std::endl;
    
    return 0;
}


/*
class Solution {
public:
    vector<ListNode*> process(ListNode* nodes) {
        vector<ListNode*> result;
        if (nodes == nullptr) {
            result.push_back(nullptr);
            result.push_back(nullptr);
            return result;
        }
        
        ListNode* slow = nodes;
        ListNode* fast = nodes->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode* secondHead = slow->next;
        slow->next = nullptr;
        
        result.push_back(nodes);
        result.push_back(secondHead);
        
        return result;
    }
};
*/