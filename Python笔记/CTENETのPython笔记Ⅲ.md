# CTENETのPython笔记Ⅲ

## Python高级特性

## 线性结构特征可迭代&切片

线性结构特征：

- 可迭代 for ... in
- 有长度 通过 len(x)获取，容器
- 通过整数下标可以访问元素。正索引、负索引
  - 可以切片
- 已经学习过的线性结构：list、tuple、str、bytes、bytearray

### 切片

```
sequence[start:stop]
sequence[start:stop:step]
```

- 通过给定的索引区间获得线性结构的一部分数据
- start、stop、step为整数，可以是正整数、负整数、零
- start为0时，可以省略
- stop为末尾时，可以省略
- step为1时，可以省略
- 切片时，索引超过上界（右边界），就取到末尾；超过下界（左边界），取到开头

```python
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(x[:])
print(x[:-1]) #
print(x[0:])
print(x[3:])
print(x[3:-1]) #
print(x[9:])
print(x[:9])
print(x[9:-1])
print(x[:100])
print(x[-100:])
print(x[4:-2])
print(x[-4:-2])
print('0123456789'[-4:8])
print(b'0123456789'[-4:8])
print(bytearray(b'0123456789')[-10:5])

# 步长
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(x[::])
print(x[::2])
print(x[2:8:3])
print(x[:9:3])
print(x[1::3])
print(x[-10:8:2])

# 起止和方向
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(x[-10:])
print(x[-5:6])
print(x[-5:-6])
print(x[6:5])
print(x[5:5])
print(x[1:9:-2])
print(x[::-2])
print(x[8::-2])
print(x[8:2:-2])
print(x[8:-10:2])
print(x[8:-10:-2])
print(x[-5:4:-1])
print(x[-5:5:-1])
```

在序列上使用切片[start:stop]，子区间索引范围[start,stop)，相当于从start开始指向stop的方向上获取数据

默认step为1，表示向右；步长为负数，表示向左

如果子区间方向和步长方向不一致，直接返回当前类型的"空对象"

如果子区间方向和步长方向一致，则从起点间隔步长取值

| 内建函数 | 函数签名   | 说明                                                     |
| -------- | ---------- | -------------------------------------------------------- |
| id       | id(object) | CPython中返回对象的内存地址 可以用来判断是不是同一个对象 |

```Python
# 使用id看地址，要注意地址回收复用问题
print(id([1,2,3]))
print(id([4,5,6,7]))
# 上下两句可能内存地址一样，但是上面那个[1,2,3]没有意义，因为它用完之后，引用计数为0了，没人能再次访问到，释放了内存
# 如果2个存在在内存中的对象，地址一样一定是同一个对象
```

```python
x = [0, 1, 2]
y = x[:]
print(x, y)
print(id(x), id(y))
x[0] = 100
print(x, y)

x = [[1]]
y = x[:]
print(x, y)
print(x == y) # True
print(id(x), id(y), x is y) # False
x[0][0] = 100
print(x, y)
print(x == y) # True
print(x is y) # False
x[0] = 200
print(x == y) # False
print(x, y)
```

上例可知，实际上切片后得到一个全新的对象。 [:] 或 [::] 相当于copy方法。

### 切片赋值

- 切片操作写在了等号左边
- 被插入的可迭代对象写在等号右边

```python
x = [0, 1, 2]
z = None
z = 1
z[:] = x # 可以吗 不可以 TypeError: 'int' object does not support item assignment
```

切片赋值用作初始化相当于copy，还可以使用。如果用在替换、插入元素，看似语法比较简洁，但是由 于列表是顺序表结构，将会引起数据的挪动，这非常影响性能，应当尽量避免使用。

## 列表、集合、字典解析式

### 列表解析式

列表解析式 List Comprehension，也叫列表推导式。

```Python
# 生成一个列表，元素0~9 将每一个元素加1后的平方值组成新的列表
x = []
for i in range(10):
    x.append((i+1)**2)
print(x)
```

```python
# 列表解析式写法
print([(i+1)**2 for i in range(10)])
```

`语法`：

- [返回值 for 元素 in 可迭代对象 if 条件]
- 使用中括号[]，内部是for循环，if条件语句可选
- 返回一个新的列表

列表解析式是一种语法糖

- 编译器会优化，不会因为简写而影响效率，反而因为有优化提高了效率
- 减少程序员代码工作量，减少出错
- 简化了代码，增强了可读性

```Python
[expr for item in iterable if cond1 if cond2]
等价于
ret = []
for item in iterable:
    if cond1:
    	if cond2:
        	ret.append(expr)
#
[expr for i in iterable1 for j in iterable2 ]
等价于
ret = []
for i in iterable1:
    for j in iterable2:
        ret.append(expr)

```

```python
# 因为循环或判断只有一个，一斜到底，所以结果相同
[(i,j) for i in range(7) if i>4 for j in range(20,25) if j>23]
[(i,j) for i in range(7) for j in range(20,25) if i>4 if j>23]
[(i,j) for i in range(7) for j in range(20,25) if i>4 and j>23]
# 都是[(5, 24), (6, 24)]
```

### 集合解析式

`语法`：

- {返回值 for 元素 in 可迭代对象 if 条件}
- 列表解析式的中括号换成花括号{}就变成了集合解析式
- 立即返回一个集合

```python
{(x, x+1) for x in range(10)}
{[x] for x in range(10)} # 可以吗？ 不可以 list是不可hash的
```

### 字典解析式

`语法`：

- {key:value for 元素 in 可迭代对象 if 条件}
- 列表解析式的中括号换成花括号{}，元素的构造使用key:value形式
- 立即返回一个字典

```python
print({x:(x,x+1) for x in range(10)})
print({x:[x,x+1] for x in range(10)})
print({(x,):[x,x+1] for x in range(10)})
# print({[x]:[x,x+1] for x in range(10)}) # 错误 key要求 可hash
print({str(x):y for x in range(3) for y in range(4)}) # 输出多少个元素？ 返回三个元素，key值唯一，{'0': 3, '1': 3, '2': 3}
```

### 解析式小结

- Python2 引入列表解析式
- Python2.4 引入生成器表达式
- Python3 引入集合、字典解析式，并迁移到了2.7

一般来说，应该多应用解析式，简短、高效。如果一个解析式非常复杂，难以读懂，要考虑拆解成for循环。

生成器和迭代器是不同的对象，但都是可迭代对象。

如果不需要立即获得所有可迭代对象的元素，在Python 3中，推荐使用惰性求值的迭代器。

| 内建函数 | 函数签名                         | 说明                                    |
| -------- | -------------------------------- | --------------------------------------- |
| sorted   | sorted(iterable[,key][,reverse]) | 默认升序，对可迭代对象排序 立即返回列表 |

```python
# 排序一定是容器内全体参与
print(sorted([1,2,3,4,5]))
print(sorted(range(10, 20), reverse=True))
print(sorted({'a':100, 'b':'abc'}))
print(sorted({'a':100, 'b':'abc'}.items()))
print(sorted({'a':'ABC', 'b':'abc'}.values(), key=str, reverse=True))
```

------

## 生成器

要创建一个生成器generator，有很多种方法

### 生成器表达式

第一种方法很简单，只要把一个列表生成式的`[]`改成`()`，就创建了一个generator

语法

- (返回值 for 元素 in 可迭代对象 if 条件)
- 列表解析式的中括号换成小括号就行了
- 返回一个生成器对象

和列表解析式的区别

- 生成器表达式是按需计算（或称惰性求值、延迟计算），需要的时候才计算值，返回可迭代对象迭代器，只能迭代一次
- 列表解析式是立即返回值，返回可迭代对象列表，不是迭代器，可反复迭代

生成器对象

- 可迭代对象
- 迭代器

**生成器表达式和列表解析式对比**

- 计算方式 
  - 生成器表达式延迟计算，列表解析式立即计算
- 内存占用 
  - 单从返回值本身来说，生成器表达式省内存，列表解析式返回新的列表
  - 生成器没有数据，内存占用极少，但是使用的时候，虽然一个个返回数据，但是合起来占用的内存也差不多
  - 列表解析式构造新的列表需要立即占用掉内存
- 计算速度 
  - 单看计算时间看，生成器表达式耗时非常短，列表解析式耗时长
  - 但生成器本身并没有返回任何值，只返回了一个生成器对象
  - 列表解析式构造并返回了一个新的列表

例子：

```python
>>> L = [x * x for x in range(10)]
>>> L
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
>>> g = (x * x for x in range(10))
>>> g
<generator object <genexpr> at 0x1022ef630>
```

创建`L`和`g`的区别仅在于最外层的`[]`和`()`，`L`是一个list，而`g`是一个generator。

我们可以直接打印出list的每一个元素，但我们怎么打印出generator的每一个元素呢？

如果要一个一个打印出来，可以通过`next()`函数获得generator的下一个返回值：

```python
>>> next(g)
0
>>> next(g)
1
>>> next(g)
4
>>> next(g)
9
>>> next(g)
16
>>> next(g)
25
>>> next(g)
36
>>> next(g)
49
>>> next(g)
64
>>> next(g)
81
>>> next(g)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

generator保存的是算法，每次调用`next(g)`，就计算出`g`的下一个元素的值，直到计算到最后一个元素，没有更多的元素时，抛出`StopIteration`的错误。

当然，上面这种不断调用`next(g)`实在是太变态了，正确的方法是使用`for`循环，因为generator也是可迭代对象：

```python
>>> g = (x * x for x in range(10))
>>> for n in g:
...     print(n)
... 
0
1
4
9
16
25
36
49
64
81
```

所以，我们创建了一个generator后，基本上永远不会调用`next()`，而是通过`for`循环来迭代它，并且不需要关心`StopIteration`的错误。

generator非常强大。如果推算的算法比较复杂，用类似列表生成式的`for`循环无法实现的时候，还可以用函数来实现。

## 生成器函数



```python
# 生成器函数 # 调用后返回什么呢？生成器对象（生成器表达式、生成器函数），惰性求值
# 在一个函数定义中，出现了yield语句，此函数就是生成器函数
def foo():
	while True:
		yield 1
# 无限可迭代对象
f = foo()
```

generator非常强大。如果推算的算法比较复杂，用类似列表生成式的`for`循环无法实现的时候，还可以用函数来实现。

比如，著名的斐波拉契数列（Fibonacci），除第一个和第二个数外，任意一个数都可由前两个数相加得到：

```
1, 1, 2, 3, 5, 8, 13, 21, 34, ...
```

斐波拉契数列用列表生成式写不出来，但是，用函数把它打印出来却很容易：



```python
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        print(b)
        a, b = b, a + b
        n = n + 1
    return 'done'
```

*注意*，赋值语句：



```python
a, b = b, a + b
```

相当于：



```python
t = (b, a + b) # t是一个tuple
a = t[0]
b = t[1]
```

但不必显式写出临时变量t就可以赋值。

上面的函数可以输出斐波那契数列的前N个数：



```python
>>> fib(6)
1
1
2
3
5
8
'done'
```

仔细观察，可以看出，`fib`函数实际上是定义了斐波拉契数列的推算规则，可以从第一个元素开始，推算出后续任意的元素，这种逻辑其实非常类似generator。

也就是说，上面的函数和generator仅一步之遥。要把`fib`函数变成generator，只需要把`print(b)`改为`yield b`就可以了：



```python
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'
```

这就是定义generator的另一种方法。如果一个函数定义中包含`yield`关键字，那么这个函数就不再是一个普通函数，而是一个generator：



```python
>>> f = fib(6)
>>> f
<generator object fib at 0x104feaaa0>
```

这里，最难理解的就是generator和函数的执行流程不一样。函数是顺序执行，遇到`return`语句或者最后一行函数语句就返回。而变成generator的函数，在每次调用`next()`的时候执行，遇到`yield`语句返回，再次执行时从上次返回的`yield`语句处继续执行。

举个简单的例子，定义一个generator，依次返回数字1，3，5：

```python
def odd():
    print('step 1')
    yield 1
    print('step 2')
    yield(3)
    print('step 3')
    yield(5)
```

调用该generator时，首先要生成一个generator对象，然后用`next()`函数不断获得下一个返回值：

```python
>>> o = odd()
>>> next(o)
step 1
1
>>> next(o)
step 2
3
>>> next(o)
step 3
5
>>> next(o)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

可以看到，`odd`不是普通函数，而是generator，在执行过程中，遇到`yield`就中断，下次又继续执行。执行3次`yield`后，已经没有`yield`可以执行了，所以，第4次调用`next(o)`就报错。

回到`fib`的例子，我们在循环过程中不断调用`yield`，就会不断中断。当然要给循环设置一个条件来退出循环，不然就会产生一个无限数列出来。

同样的，把函数改成generator后，我们基本上从来不会用`next()`来获取下一个返回值，而是直接使用`for`循环来迭代：

```python
>>> for n in fib(6):
...     print(n)
...
1
1
2
3
5
8
```

但是用`for`循环调用generator时，发现拿不到generator的`return`语句的返回值。如果想要拿到返回值，必须捕获`StopIteration`错误，返回值包含在`StopIteration`的`value`中：

```python
>>> g = fib(6)
>>> while True:
...     try:
...         x = next(g)
...         print('g:', x)
...     except StopIteration as e:
...         print('Generator return value:', e.value)
...         break
...
g: 1
g: 1
g: 2
g: 3
g: 5
g: 8
Generator return value: done
```

关于如何捕获错误，后面的错误处理还会详细讲解。

## 迭代器

我们已经知道，可以直接作用于`for`循环的数据类型有以下几种：

一类是集合数据类型，如`list`、`tuple`、`dict`、`set`、`str`等；

一类是`generator`，包括生成器和带`yield`的generator function。

这些可以直接作用于`for`循环的对象统称为可迭代对象：`Iterable`。

可以使用`isinstance()`判断一个对象是否是`Iterable`对象：

------

```Python
>>> from collections.abc import Iterable
>>> isinstance([], Iterable)
True
>>> isinstance({}, Iterable)
True
>>> isinstance('abc', Iterable)
True
>>> isinstance((x for x in range(10)), Iterable)
True
>>> isinstance(100, Iterable)
False
```

而生成器不但可以作用于`for`循环，还可以被`next()`函数不断调用并返回下一个值，直到最后抛出`StopIteration`错误表示无法继续返回下一个值了。

可以被`next()`函数调用并不断返回下一个-值的对象称为迭代器：`Iterator`。

可以使用`isinstance()`判断一个对象是否是`Iterator`对象：

```python
>>> from collections.abc import Iterator
>>> isinstance((x for x in range(10)), Iterator)
True
>>> isinstance([], Iterator)
False
>>> isinstance({}, Iterator)
False
>>> isinstance('abc', Iterator)
False
```

生成器都是`Iterator`对象，但`list`、`dict`、`str`虽然是`Iterable`，却不是`Iterator`。

把`list`、`dict`、`str`等`Iterable`变成`Iterator`可以使用`iter()`函数：

```python
>>> isinstance(iter([]), Iterator)
True
>>> isinstance(iter('abc'), Iterator)
True
```

你可能会问，为什么`list`、`dict`、`str`等数据类型不是`Iterator`？

这是因为Python的`Iterator`对象表示的是一个数据流，Iterator对象可以被`next()`函数调用并不断返回下一个数据，直到没有数据时抛出`StopIteration`错误。可以把这个数据流看做是一个有序序列，但我们却不能提前知道序列的长度，只能不断通过`next()`函数实现按需计算下一个数据，所以`Iterator`的计算是惰性的，只有在需要返回下一个数据时它才会计算。

`Iterator`甚至可以表示一个无限大的数据流，例如全体自然数。而使用list是永远不可能存储全体自然数的。

### **小结**

凡是可作用于`for`循环的对象都是`Iterable`类型；

凡是可作用于`next()`函数的对象都是`Iterator`类型，它们表示一个惰性计算的序列；

集合数据类型如`list`、`dict`、`str`等是`Iterable`但不是`Iterator`，不过可以通过`iter()`函数获得一个`Iterator`对象。

Python的`for`循环本质上就是通过不断调用`next()`函数实现的，例如：

```python
for x in [1, 2, 3, 4, 5]:
    pass
```

实际上完全等价于：

```python
# 首先获得Iterator对象:
it = iter([1, 2, 3, 4, 5])
# 循环:
while True:
    try:
        # 获得下一个值:
        x = next(it)
    except StopIteration:
        # 遇到StopIteration就退出循环
        break
```

迭代器

- 特殊的对象，一定是可迭代对象，具备可迭代对象的特征
- 通过 iter 方法把一个可迭代对象封装成迭代器
- 通过 next 方法，迭代 迭代器对象
- 生成器对象，就是迭代器对象。但是迭代器对象未必是生成器对象

可迭代对象

- 能够通过迭代一次次返回不同的元素的对象 
  - 所谓相同，不是指值是否相同，而是元素在容器中是否是同一个，例如列表中值可以重复的，['a', 'a']，虽然这个列表有2个元素，值一样，但是两个'a'是不同的元素
- 可以迭代，但是未必有序，未必可索引
- 可迭代对象有：list、tuple、string、bytes、bytearray、range、set、dict、生成器、迭代器等
- 可以使用成员操作符in、not in 
  - 对于线性数据结构，in本质上是在遍历对象，时间复杂度为O(n)

```python
lst = [1, 3, 5, 7, 9]
it = iter(lst) # 返回一个迭代器对象
print(next(it)) # 1
print(next(it)) # 3
for i, x in enumerate(it, 2):
    print(i, x)
#2 5
#3 7
#4 9

# print(next(it)) # StopIteration
print()

for x in reversed(lst):
    print(x) # 9 7 5 3 1
```

