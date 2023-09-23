"""
使用Python解决一道算法题：给一个整数columnNumber，返回它在Excel表中对应的列名称。
例如：
输入：2 输出：b
输入：3 输出：c
输入：26 输出：z
输入：27 输出：aa

给出完整的Python代码
"""
import sys


def convertToTitle(columnNumber):
    result = ""
    while columnNumber > 0:
        columnNumber -= 1
        remainder = columnNumber % 26
        result = chr(97 + remainder) + result
        columnNumber //= 26
    return result

print(convertToTitle(int(input())))
