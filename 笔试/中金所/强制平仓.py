"""
使用Python解决一道算法题：
交易所发现某客户持仓过多时，需要对其超出的持仓进行强制平仓，即强制减少持仓量，假设某客户需要强制平仓n手，每次只平仓一手或两手，问有多少种平仓方法？
输入：n（需要平仓的手数）
输出：平仓方法数
给出完整的Python代码
"""
"""
函数使用递归的方式计算平仓方法数。当需要平仓的手数为0时，只有一种平仓方法；当需要平仓的手数为1时，也只有一种平仓方法；当需要平仓的手数为2时，有两种平仓方法。对于其他手数，可以通过将最后一次平仓的手数设为1或2来计算平仓方法数。最后，通过输入需要平仓的手数，调用函数并输出平仓方法数。
"""
def count_closure_methods(n):
    if n == 0:
        return 1
    elif n == 1:
        return 1
    elif n == 2:
        return 2
    else:
        return count_closure_methods(n-1) + count_closure_methods(n-2)

n = int(input())
methods = count_closure_methods(n)
print(methods)


#优化
def count_closure_methods(n):
    if n == 0:
        return 1
    elif n == 1:
        return 1
    elif n == 2:
        return 2
    else:
        dp = [0] * (n+1)
        dp[0] = 1
        dp[1] = 1
        dp[2] = 2
        for i in range(3, n+1):
            dp[i] = dp[i-1] + dp[i-2]
        return dp[n]

n = int(input())
methods = count_closure_methods(n)
print(methods)