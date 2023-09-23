"""
小红认为两个字符串相似，需要这两个字符串的每个字母的个数都相等。如"abcbd"和"dbcba"相似，"abcd"和"abcd"相似。 而"abb"和"aab"不相似，"ac"和"cca"不相似。现在小红有n个字符串,她想知道有多少对字符串是相似的?
输入一个整数n，接下来n行，每行输入一个仅包含小写字母的字符串s
输出一个整数
"""

def count_similar_strings(n, strings):
    count = 0
    sorted_strings = [''.join(sorted(s)) for s in strings]
    freq = {}
    for s in sorted_strings:
        freq[s] = freq.get(s, 0) + 1
    for value in freq.values():
        count += value * (value - 1) // 2
    return count

n = int(input())
strings = []
for _ in range(n):
    strings.append(input())

result = count_similar_strings(n, strings)
print(result)
