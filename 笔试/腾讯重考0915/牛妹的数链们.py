#牛妹有一堆数链，这些数链里面的数字都杂乱无章，牛妹想整理一下这些数字，把它们从小到大排成一个数链
# 如 输入 {{1,3,5},{2,4,6},{1,2,3,4,5,6}}
# 输出 {1,1,2,2,3,3,4,4,5,5,6,6}

# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

#
# 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
# 返回一个指向链表头部的指针。
# @param a ListNode类一维数组 指向这些数链的开头
# @return ListNode类
#
# 第一题 打卡题

#  超时 用例通过率为40%
class Solution:
    def solve(self, a):
        # 将所有数链的节点值存入一个列表
        values = []
        for node in a:
            while node:
                values.append(node.val)
                node = node.next
        
        # 对列表进行排序
        values.sort()
        
        # 根据排序后的列表构建新的数链
        dummy = ListNode(0)
        curr = dummy
        for val in values:
            curr.next = ListNode(val)
            curr = curr.next
        
        return dummy.next

