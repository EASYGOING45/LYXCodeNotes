# 剑指Offer 06-从尾到头打印链表

![image-20230126102915030](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230126102915030.png)

## 思路

- 递归
- 翻转
- 辅助栈

## 代码

### 递归

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) 
    {
        //递归
        if(head == nullptr)
        {
            return {};
        }
        vector<int> res=reversePrint(head->next);
        res.push_back(head->val);
        return res;
    }
};
```

### 翻转

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) 
    {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur)
        {
            //翻转链表
            ListNode* next=cur->next;
            cur->next = pre;
            pre=cur;
            cur=next;
        }
        vector<int> res;
        while(pre)
        {
            res.push_back(pre->val);
            pre = pre->next;
        }
        return res;
    }
};
```

![image-20230126103344072](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230126103344072.png)