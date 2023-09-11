n = int(input())
a = list(map(int, input().split()))

courage = 0
max_courage = 0

for i in range(n):
    if a[i] > courage:
        max_courage += a[i] - courage
        courage = a[i]
    else:
        courage = a[i]

print(max_courage)