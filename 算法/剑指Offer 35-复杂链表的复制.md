# 剑指Offer 35-复杂链表的复制

![image-20230126104723550](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230126104723550.png)

## 思路

- 哈希表
- 利用回溯的方式，让每个节点的拷贝操作相互独立。对于当前节点，我们首先要进行拷贝，然后我们进行「当前节点的后继节点」和「当前节点的随机指针指向的节点」拷贝，拷贝完成后将创建的新节点的指针返回，即可完成当前节点的两指针的赋值。


## 代码

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    unordered_map<Node*,Node*> cacheNode;
    Node* copyRandomList(Node* head) 
    {
        if(head ==nullptr)
        {
            return nullptr;
        }
        if(!cacheNode.count(head))
        {
            Node* headNew = new Node(head->val);
            cacheNode[head]=headNew;
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        return cacheNode[head];
    }
};
```

