import heapq

'''
小Q有一个长度为n的数组，它对这个数组有k次操作机会，操作如下：
可以选择数组中的任意一个数字并改变它
1、如果选择的数字x是奇数，那么这个奇数乘以2，即x=x*2
2、如果选择的数字x是偶数，那么这个偶数乘以2再加1，即x=x*2+1
小Q想让这k次操作之后，数组元素之和最小，请你输出这个最小值是多少？
保证最终的元素之和不超过10的18次方

输入描述：
第一行输入两个正整数n和k，用空格隔开
第二行输入n哥正整数ai，代表数组的每个元素

输出一个整数，代表k次操作之后，数组元素之和的最小值
'''

#通过使用堆数据结构，可以在每次操作中快速找到最小值，并且避免了重复计算，从而提高了代码的效率。

n, k = map(int, input().split())
arr = list(map(int, input().split()))

# 使用堆来维护数组中的最小值
heap = []
for i in range(n):
    heapq.heappush(heap, arr[i])

# 对最小值进行k次操作
for i in range(k):
    # 找到当前最小值
    min_val = heapq.heappop(heap)
    
    # 如果最小值是奇数，将其乘以2
    if min_val % 2 == 1:
        min_val *= 2
    # 如果最小值是偶数，将其乘以2再加1
    else:
        min_val = min_val * 2 + 1
    
    # 将操作后的值重新加入堆中
    heapq.heappush(heap, min_val)

# 计算数组元素之和
sum_val = sum(heap)

# 输出数组元素之和的最小值
print(sum_val)



""" 超时代码
n, k = map(int, input().split())
arr = list(map(int, input().split()))

# 对数组中的每个元素进行k次操作
for i in range(k):
    # 找到数组中的最小值
    min_val = min(arr)
    # 找到最小值在数组中的索引
    min_idx = arr.index(min_val)
    
    # 如果最小值是奇数，将其乘以2
    if min_val % 2 == 1:
        arr[min_idx] *= 2
    # 如果最小值是偶数，将其乘以2再加1
    else:
        arr[min_idx] = arr[min_idx] * 2 + 1

# 输出数组元素之和的最小值
print(sum(arr))
"""