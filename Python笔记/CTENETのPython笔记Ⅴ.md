# CTENETのPython笔记Ⅴ

## 函数式编程

## 高阶函数

一等公民：

- 函数在python中是一等公民（First-Class Object）
- 函数也是对象，是可调用对象
- 函数可以作为普通变量，也可以作为函数的参数、返回值

高级函数：高阶函数（High-order Function）

- 数学概念y=f(g(x))

- 在数学和计算机科学中，高阶函数应当是至少满足下面一个条件的函数

  - 接受一个或多个函数作为参数
  - 输出一个函数

  ```Python
  def counter(base):
      def inc(step=1): # 有没有闭包？
          nonlocal base # 形参base也是外部函数counter的local变量
          base += step
          return base
      return inc
  c1 = counter(5)
  print(c1())
  print(c1())
  print(c1())
  c2 = counter(5)
  print(c2())
  print(c1 == c2) # 相等吗？ 不相等，两个不同的实例
  ```

### 内建函数

### map/reduce

Python内建了`map()`和`reduce()`函数。

如果你读过Google的那篇大名鼎鼎的论文“[MapReduce: Simplified Data Processing on Large Clustersopen in new window](http://research.google.com/archive/mapreduce.html)”，你就能大概明白map/reduce的概念。

我们先看map。`map()`函数接收两个参数，一个是函数，一个是`Iterable`，`map`将传入的函数依次作用到序列的每个元素，并把结果作为新的`Iterator`返回。

举例说明，比如我们有一个函数f(x)=x2，要把这个函数作用在一个list `[1, 2, 3, 4, 5, 6, 7, 8, 9]`上，就可以用`map()`实现如下：

```ascii
            f(x) = x * x

                  │
                  │
  ┌───┬───┬───┬───┼───┬───┬───┬───┐
  │   │   │   │   │   │   │   │   │
  ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼

[ 1   2   3   4   5   6   7   8   9 ]

  │   │   │   │   │   │   │   │   │
  │   │   │   │   │   │   │   │   │
  ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼

[ 1   4   9  16  25  36  49  64  81 ]
```

现在，我们用Python代码实现：

```python
>>> def f(x):
...     return x * x
...
>>> r = map(f, [1, 2, 3, 4, 5, 6, 7, 8, 9])
>>> list(r)
[1, 4, 9, 16, 25, 36, 49, 64, 81]
```

`map()`传入的第一个参数是`f`，即函数对象本身。由于结果`r`是一个`Iterator`，`Iterator`是惰性序列，因此通过`list()`函数让它把整个序列都计算出来并返回一个list。

你可能会想，不需要`map()`函数，写一个循环，也可以计算出结果：

```python
L = []
for n in [1, 2, 3, 4, 5, 6, 7, 8, 9]:
    L.append(f(n))
print(L)
```

的确可以，但是，从上面的循环代码，能一眼看明白“把f(x)作用在list的每一个元素并把结果生成一个新的list”吗？

所以，`map()`作为高阶函数，事实上它把运算规则抽象了，因此，我们不但可以计算简单的f(x)=x2，还可以计算任意复杂的函数，比如，把这个list所有数字转为字符串：

```python
>>> list(map(str, [1, 2, 3, 4, 5, 6, 7, 8, 9]))
['1', '2', '3', '4', '5', '6', '7', '8', '9']
```

只需要一行代码。

再看`reduce`的用法。`reduce`把一个函数作用在一个序列`[x1, x2, x3, ...]`上，这个函数必须接收两个参数，`reduce`把结果继续和序列的下一个元素做累积计算，其效果就是：

```python
reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)
```

比方说对一个序列求和，就可以用`reduce`实现：

```python
>>> from functools import reduce
>>> def add(x, y):
...     return x + y
...
>>> reduce(add, [1, 3, 5, 7, 9])
25
```

当然求和运算可以直接用Python内建函数`sum()`，没必要动用`reduce`。

但是如果要把序列`[1, 3, 5, 7, 9]`变换成整数`13579`，`reduce`就可以派上用场：

```python
>>> from functools import reduce
>>> def fn(x, y):
...     return x * 10 + y
...
>>> reduce(fn, [1, 3, 5, 7, 9])
13579
```

这个例子本身没多大用处，但是，如果考虑到字符串`str`也是一个序列，对上面的例子稍加改动，配合`map()`，我们就可以写出把`str`转换为`int`的函数：

```python
>>> from functools import reduce
>>> def fn(x, y):
...     return x * 10 + y
...
>>> def char2num(s):
...     digits = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}
...     return digits[s]
...
>>> reduce(fn, map(char2num, '13579'))
13579
```

整理成一个`str2int`的函数就是：

```python
from functools import reduce

DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

def str2int(s):
    def fn(x, y):
        return x * 10 + y
    def char2num(s):
        return DIGITS[s]
    return reduce(fn, map(char2num, s))
```

还可以用lambda函数进一步简化成：

```python
from functools import reduce

DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

def char2num(s):
    return DIGITS[s]

def str2int(s):
    return reduce(lambda x, y: x * 10 + y, map(char2num, s))
```

也就是说，假设Python没有提供`int()`函数，你完全可以自己写一个把字符串转化为整数的函数，而且只需要几行代码！

lambda函数的用法在后面介绍。

### 过滤 filter

Python内建的`filter()`函数用于过滤序列。

和`map()`类似，`filter()`也接收一个函数和一个序列。和`map()`不同的是，`filter()`把传入的函数依次作用于每个元素，然后根据返回值是`True`还是`False`决定保留还是丢弃该元素。

例如，在一个list中，删掉偶数，只保留奇数，可以这么写：

```python
def is_odd(n):
    return n % 2 == 1

list(filter(is_odd, [1, 2, 4, 5, 6, 9, 10, 15]))
# 结果: [1, 5, 9, 15]
```

把一个序列中的空字符串删掉，可以这么写：

```python
def not_empty(s):
    return s and s.strip()

list(filter(not_empty, ['A', '', 'B', None, 'C', '  ']))
# 结果: ['A', 'B', 'C']
```

可见用`filter()`这个高阶函数，关键在于正确实现一个“筛选”函数。

注意到`filter()`函数返回的是一个`Iterator`，也就是一个惰性序列，所以要强迫`filter()`完成计算结果，需要用`list()`函数获得所有结果并返回list。

**用filter求素数**

计算[素数open in new window](http://baike.baidu.com/view/10626.htm)的一个方法是[埃氏筛法open in new window](http://baike.baidu.com/view/3784258.htm)，它的算法理解起来非常简单：

首先，列出从`2`开始的所有自然数，构造一个序列：

2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, ...

取序列的第一个数`2`，它一定是素数，然后用`2`把序列的`2`的倍数筛掉：

3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, ...

取新序列的第一个数`3`，它一定是素数，然后用`3`把序列的`3`的倍数筛掉：

5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, ...

取新序列的第一个数`5`，然后用`5`把序列的`5`的倍数筛掉：

7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, ...

不断筛下去，就可以得到所有的素数。

用Python来实现这个算法，可以先构造一个从`3`开始的奇数序列：

```python
def _odd_iter():
    n = 1
    while True:
        n = n + 2
        yield n
```

注意这是一个生成器，并且是一个无限序列。

然后定义一个筛选函数：

```python
def _not_divisible(n):
    return lambda x: x % n > 0
```

最后，定义一个生成器，不断返回下一个素数：

```python
def primes():
    yield 2
    it = _odd_iter() # 初始序列
    while True:
        n = next(it) # 返回序列的第一个数
        yield n
        it = filter(_not_divisible(n), it) # 构造新序列
```

这个生成器先返回第一个素数`2`，然后，利用`filter()`不断产生筛选后的新的序列。

由于`primes()`也是一个无限序列，所以调用时需要设置一个退出循环的条件：

```python
# 打印1000以内的素数:
for n in primes():
    if n < 1000:
        print(n)
    else:
        break
```

注意到`Iterator`是惰性计算的序列，所以我们可以用Python表示“全体自然数”，“全体素数”这样的序列，而代码非常简洁。

> function 参数如果是 None，可迭代对象的每一个元素自身等效布尔值

```python
print(list(filter(None, range(-5, 5))))
```

### 排序算法 sorted

排序也是在程序中经常用到的算法。无论使用冒泡排序还是快速排序，排序的核心是比较两个元素的大小。如果是数字，我们可以直接比较，但如果是字符串或者两个dict呢？直接比较数学上的大小是没有意义的，因此，比较的过程必须通过函数抽象出来。

Python内置的`sorted()`函数就可以对list进行排序：

```python
>>> sorted([36, 5, -12, 9, -21])
[-21, -12, 5, 9, 36]
```

此外，`sorted()`函数也是一个高阶函数，它还可以接收一个`key`函数来实现自定义的排序，例如按绝对值大小排序：

```python
>>> sorted([36, 5, -12, 9, -21], key=abs)
[5, 9, -12, -21, 36]
```

key指定的函数将作用于list的每一个元素上，并根据key函数返回的结果进行排序。对比原始的list和经过`key=abs`处理过的list：

```text
list = [36, 5, -12, 9, -21]

keys = [36, 5,  12, 9,  21]
```

然后`sorted()`函数按照keys进行排序，并按照对应关系返回list相应的元素：

```ascii
keys排序结果 => [5, 9,  12,  21, 36]
                |  |    |    |   |
最终结果     => [5, 9, -12, -21, 36]
```

我们再看一个字符串排序的例子：

```text
>>> sorted(['bob', 'about', 'Zoo', 'Credit'])
['Credit', 'Zoo', 'about', 'bob']
```

默认情况下，对字符串排序，是按照ASCII的大小比较的，由于`'Z' < 'a'`，结果，大写字母`Z`会排在小写字母`a`的前面。

现在，我们提出排序应该忽略大小写，按照字母序排序。要实现这个算法，不必对现有代码大加改动，只要我们能用一个key函数把字符串映射为忽略大小写排序即可。忽略大小写来比较两个字符串，实际上就是先把字符串都变成大写（或者都变成小写），再比较。

这样，我们给`sorted`传入key函数，即可实现忽略大小写的排序：

```text
>>> sorted(['bob', 'about', 'Zoo', 'Credit'], key=str.lower)
['about', 'bob', 'Credit', 'Zoo']
```

要进行反向排序，不必改动key函数，可以传入第三个参数`reverse=True`：

```text
>>> sorted(['bob', 'about', 'Zoo', 'Credit'], key=str.lower, reverse=True)
['Zoo', 'Credit', 'bob', 'about']
```

从上述例子可以看出，高阶函数的抽象能力是非常强大的，而且，核心代码可以保持得非常简洁。

#### **小结**

`sorted()`也是一个高阶函数。用`sorted()`排序的关键在于实现一个映射函数。

### 拉链函数 zip

- zip(*iterables)
- 像拉链一样，把多个可迭代对象合并在一起，返回一个迭代器
- 将每次从不同对象中取到的元素合并成一个元组

```python
print(list(zip(range(10),range(10))))
print(list(zip(range(10),range(10),range(5),range(10))))
print(dict(zip(range(10),range(10))))

d1 = {str(x):y for x,y in zip(range(10),range(10))} # 字典解析式
print(d1)
```

## 返回函数

### 柯里化

- 指的是将原来接受两个参数的函数变成新的接受一个参数的函数的过程。新的函数返回一个以原有第二个参数为参数的函数
- z = f(x, y) 转换成 z = f(x)(y) 的形式

例如

```python
def add(x, y):
    return x + y
```

原来函数调用为 add(4, 5) ，柯里化目标是 add(4)(5) 。如何实现？

每一次括号说明是函数调用，说明 add(4)(5) 是2次函数调用。

```text
add(4)(5)
等价于
t = add(4)
t(5)
```

也就是说add(4)应该返回函数

```python
def add(x):
    def _add(y):
        return x + y
    return _add
print(add(100)(200))
```

通过嵌套函数就可以把函数转成柯里化函数。

### 函数作为返回值

高阶函数除了可以接受函数作为参数外，还可以把函数作为结果值返回。

我们来实现一个可变参数的求和。通常情况下，求和的函数是这样定义的：

```python
def calc_sum(*args):
    ax = 0
    for n in args:
        ax = ax + n
    return ax
```

但是，如果不需要立刻求和，而是在后面的代码中，根据需要再计算怎么办？可以不返回求和的结果，而是返回求和的函数：

```python
def lazy_sum(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum
```

当我们调用`lazy_sum()`时，返回的并不是求和结果，而是求和函数：

```python
>>> f = lazy_sum(1, 3, 5, 7, 9)
>>> f
<function lazy_sum.<locals>.sum at 0x101c6ed90>
```

调用函数`f`时，才真正计算求和的结果：

```python
>>> f()
25
```

在这个例子中，我们在函数`lazy_sum`中又定义了函数`sum`，并且，内部函数`sum`可以引用外部函数`lazy_sum`的参数和局部变量，当`lazy_sum`返回函数`sum`时，相关参数和变量都保存在返回的函数中，这种称为“闭包（Closure）”的程序结构拥有极大的威力。

请再注意一点，当我们调用`lazy_sum()`时，每次调用都会返回一个新的函数，即使传入相同的参数：

```python
>>> f1 = lazy_sum(1, 3, 5, 7, 9)
>>> f2 = lazy_sum(1, 3, 5, 7, 9)
>>> f1==f2
False
```

`f1()`和`f2()`的调用结果互不影响。

### 闭包

注意到返回的函数在其定义内部引用了局部变量`args`，所以，当一个函数返回了一个函数后，其内部的局部变量还被新函数引用，所以，闭包用起来简单，实现起来可不容易。

另一个需要注意的问题是，返回的函数并没有立刻执行，而是直到调用了`f()`才执行。我们来看一个例子：

```python
def count():
    fs = []
    for i in range(1, 4):
        def f():
             return i*i
        fs.append(f)
    return fs

f1, f2, f3 = count()
```

在上面的例子中，每次循环，都创建了一个新的函数，然后，把创建的3个函数都返回了。

你可能认为调用`f1()`，`f2()`和`f3()`结果应该是`1`，`4`，`9`，但实际结果是：

```python
>>> f1()
9
>>> f2()
9
>>> f3()
9
```

全部都是`9`！原因就在于返回的函数引用了变量`i`，但它并非立刻执行。等到3个函数都返回时，它们所引用的变量`i`已经变成了`3`，因此最终结果为`9`。

返回闭包时牢记一点：返回函数不要引用任何循环变量，或者后续会发生变化的变量。

如果一定要引用循环变量怎么办？方法是再创建一个函数，用该函数的参数绑定循环变量当前的值，无论该循环变量后续如何更改，已绑定到函数参数的值不变：

```python
def count():
    def f(j):
        def g():
            return j*j
        return g
    fs = []
    for i in range(1, 4):
        fs.append(f(i)) # f(i)立刻被执行，因此i的当前值被传入f()
    return fs
```

再看看结果：

```python
>>> f1, f2, f3 = count()
>>> f1()
1
>>> f2()
4
>>> f3()
9
```

缺点是代码较长，可利用lambda函数缩短代码。

## 匿名函数

Python中，匿名函数也叫lambda表达式。

匿名：隐藏名字，即没有名称。

匿名函数：没有名字的函数

函数没有名字该如何定义？函数没有名字如何调用？

### Lambda表达式

Python中，使用Lambda表达式构建匿名函数

```Python
def foo(x):
    return x**2
lambda x: x ** 2  # 定义

a=(lambda x: x ** 2)(4) # 调用
print(a)

foo = lambda x,y: (x+y) ** 2 # 定义函数
print(foo(1,2))
# 等价于
def foo(x,y):
    return (x+y) ** 2
```

- 使用lambda关键字定义匿名函数，格式为lambda [参数列表]:表达式
- 参数列表不需要小括号。无参就不写参数
- 冒号用来分割参数列表和表达式部分
- 不需要使用return。表达式的值，就是匿名函数的返回值。表达式中不能出现等号
- Python的lambda表达式（匿名函数）只能写在一行上，也称为单行函数

匿名函数往往用在为高阶函数传参时，使用lambda表达式，往往能简化代码

```Python
# 返回常量的函数
print((lambda :3)())

# 加法匿名函数，带缺省值
print((lambda x, y=3: x + y)(5))
print((lambda x, y=3: x + y)(5, 6))

# keyword-only参数
print((lambda x, *, y=30: x + y)(5))
print((lambda x, *, y=30: x + y)(5, y=10))

# 可变参数
print((lambda *args: (x for x in args))(*range(5))) # 生成器
print((lambda *args: [x+1 for x in args])(*range(5))) # 列表
print((lambda *args: {x%2 for x in args})(*range(5))) # 集合
print((lambda *args: {str(x):x for x in args})(*range(5))) # 字典

print(dict(map(lambda x: (chr(65+x), 10-x), range(5)))) # 高阶函数，构建字典

d = dict(map(lambda x: (chr(65+x), 10-x), range(5))) # 高阶函数
a = sorted(d.items(), key=lambda x:x[1])
print(a)
```

## 装饰器

### 由来

需求：为一个加法函数增加记录实参的功能

```python
def add(x, y):
    print('add called. x={}, y={}'.format(x, y)) # 增加的记录功能
    return x + y

add(4, 5)
```

上面的代码满足了需求，但有缺点：

记录信息的功能，可以是一个单独的功能。显然和add函数耦合太紧密。加法函数属于业务功能，输出信息属于非功能代码，不该放在add函数中

1、提供一个函数logger完成记录功能

```python
def add(x, y):
    return x + y

def logger(fn):
    print('调用前增强')
    ret = fn(4, 5)
    print('调用后增强')
    return ret

print(logger(add))
```

2、改进传参

```python
def add(x, y):
    return x + y

def logger(fn, *args, **kwargs):
    print('调用前增强')
    ret = fn(*args, **kwargs)
    print('调用后增强')
    return ret

print(logger(add, 4, 5))
```

3、柯里化

```python
def add(x, y):
    return x + y

def logger(fn):
    def wrapper( *args, **kwargs):
        print('调用前增强')
        ret = fn(*args, **kwargs)
        print('调用后增强')
        return ret
    return wrapper

inner = logger(add)
x = inner(4, 5)
print(x)
```

再进一步

```python
def add(x, y):
    return x + y

def logger(fn):
    def wrapper( *args, **kwargs):
        print('调用前增强')
        ret = fn(*args, **kwargs)
        print('调用后增强')
        return ret
    return wrapper

add = logger(add)
print(add(4, 5))
```

4、装饰器语法

```python
def logger(fn):
    def wrapper( *args, **kwargs):
        print('调用前增强')
        ret = fn(*args, **kwargs)
        print('调用后增强')
        return ret
    return wrapper

@logger # 等价于 add = wrapper <=> add = logger(add)
def add(x, y):
    return x + y

print(add(4, 5))
```

@logger就是装饰器语法

***等价式非常重要，如果你不能理解装饰器，开始的时候一定要把等价式写在后面***

### 无参装饰器

- 上例的装饰器语法，称为无参装饰器
- @符号后是一个函数
- 虽然是无参装饰器，但是@后的函数本质上是单参函数
- 上例的 logger 函数是一个高阶函数

### 日志记录装饰器实现

```python
import time
import datetime

def logger(fn):
    def wrapper(*args, **kwargs):
        print('调用前增强')
        start = datetime.datetime.now()
        ret = fn(*args, **kwargs) # 参数解构
        print('调用后增强')
        delta = (datetime.datetime.now() - start).total_seconds()
        print('Function {} took {}s.'.format(fn.__name__, delta))
        return ret
    return wrapper

@logger # 等价于 add = wrapper <=> add = logger(add)
def add(x, y):
    time.sleep(2)
    return x + y

print(add(100, 200))
```

### 文档字符串

- Python 文档字符串 Documentation Strings
- 在函数（类、模块）语句块的第一行，且习惯是多行的文本，所以多使用三引号
- 文档字符串也算是合法的一条语句
- 惯例是首字母大写，第一行写概述，空一行，第三行写详细描述
- 可以使用特殊属性__doc__访问这个文档

```python
def add(x, y):
    """这是加法函数的文档"""
    return x + y

print("{}'s doc = {}".format(add.__name__ , add.__doc__))
```

```python
import time
import datetime

def logger(fn):
    def wrapper(*args, **kwargs):
        '''wrapper's doc'''
        print('调用前增强')
        start = datetime.datetime.now()
        ret = fn(*args, **kwargs) # 参数解构
        print('调用后增强')
        delta = (datetime.datetime.now() - start).total_seconds()
        print('Function {} took {}s.'.format(fn.__name__, delta))
        return ret
    return wrapper

@logger # 等价于 add = wrapper <=> add = logger(add)
def add(x, y):
    '''add's doc'''
    time.sleep(0.1)
    return x + y

print(add(100, 200))

print("name={}, doc={}".format(add.__name__, add.__doc__))
```

被装饰后，函数名和文档都不对了。如何解决？

**functools模块**提供了一个wraps装饰器函数，本质上调用的是update_wrapper，它就是一个属性复制函数。

wraps(wrapped, assigned=WRAPPER_ASSIGNMENTS, updated=WRAPPER_UPDATES)

- wrapped 就是被包装函数
- wrapper 就是包装函数
- 用被包装函数的属性覆盖包装函数的同名属性
- 元组 WRAPPER_ASSIGNMENTS 中是要被覆盖的属性 
  - `__module__` , `__name__` , `__qualname__` , `__doc__` , `__annotations__`
  - 模块名、名称、限定名、文档、参数注解

```python
import time
import datetime
from functools import wraps

def logger(fn):
    @wraps(fn) # 用被包装函数fn的属性覆盖包装函数wrapper的同名属性
    def wrapper(*args, **kwargs):
        '''wrapper's doc'''
        print('调用前增强')
        start = datetime.datetime.now()
        ret = fn(*args, **kwargs) # 参数解构
        print('调用后增强')
        delta = (datetime.datetime.now() - start).total_seconds()
        print('Function {} took {}s.'.format(fn.__name__, delta))
        return ret
    return wrapper

@logger # 等价于 add = wrapper <=> add = logger(add)
def add(x, y):
    '''add's doc'''
    time.sleep(0.1)
    return x + y

print(add(100, 200))

print("name={}, doc={}".format(add.__name__, add.__doc__))
```

### 带参装饰器

- @之后不是一个单独的标识符，是一个函数调用
- 函数调用的返回值又是一个函数，此函数是一个无参装饰器
- 带参装饰器，可以有任意个参数 
  - @func()
  - @func(1)
  - @func(1, 2)

### 进阶

```python
import datetime
from functools import wraps

def logger(fn):
    print('logger run')
    @wraps(fn) # 用被包装函数fn的属性覆盖包装函数wrapper的同名属性
    def wrapper(*args, **kwargs): # wrapper = wraps(fn)(wrapper)
        "wrapper's doc"
        print('wrapper run')
        start = datetime.datetime.now()
        ret = fn(*args, **kwargs) # 参数解构
        delta = (datetime.datetime.now() - start).total_seconds()
        print('Function {} took {}s.'.format(fn.__name__, delta))
        return ret
    return wrapper

@logger # 等价于 add = wrapper <=> add = logger(add)
def add(x, y):
    """add function"""

@logger
def sub(x, y):
    """sub function"""

print(add.__name__, sub.__name__)
```

- logger 什么时候执行？ 从上到下执行
- logger 执行过几次？ 两次
- wraps 装饰器执行过几次？ 两次 ， 也是进入函数，从上到下依次执行，函数没调用前，跳过函数部分代码
- wrapper 的 `__name__` 等属性被覆盖过几次？ 两次
- `add.__name__` 打印什么名称？add
- `sub.__name__` 打印什么名称？sub

### 时间模块

#### datetime 模块

datetime类

- 时间高级类
- 类方法，即使用类调用的方法，由类方法获得一个时间对象 
  - now(tz=None) 返回当前时间的datetime对象，时间到微秒，如果tz为None，返回当前时区的不带时区信息的时间
  - utcnow() 不带时区的0时区时间
  - fromtimestamp(timestamp, tz=None) 从一个时间戳返回一个datetime对象
- 时间对象方法 
  - timestamp() 返回一个到微秒的时间戳 
    - 时间戳：格林威治时间1970年1月1日0点到现在的秒数
  - 构造方法 datetime.datetime(2016, 12, 6, 16, 29, 43, 79043)
  - year、month、day、hour、minute、second、microsecond，取datetime对象的年月日时分秒及微秒
  - weekday() 返回星期的天，周一0，周日6
  - isoweekday() 返回星期的天，周一1，周日7
  - date() 返回日期date对象
  - time() 返回时间time对象

```python
import datetime

# 类方法获得时间对象
print(datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=8)))) # 时区时间
print(datetime.datetime.now()) # 无时区时间
print(datetime.datetime.utcnow()) # UTC时间，可以认为是GMT或0时区时间

# 时间戳操作
stamp = datetime.datetime.now().timestamp() # 获得时间戳
print(stamp)
dt = datetime.datetime.fromtimestamp(stamp) # 从时间戳获得时间对象
print(dt)

print(type(dt.date()), dt.date())
print(type(dt.time()), dt.time())
```

#### 日期与格式化

- 类方法 strptime(date_string, format) ，返回datetime对象（时间字符串+格式化字符串 => 时间对象）
- 对象方法 strftime(format) ，返回字符串（时间对象通过格式字符串 => 时间字符串）
- 字符串format函数格式化（时间对象通过格式字符串 => 时间字符串）

```python
import datetime

datestr = '2018-01-10 17:16:08'
dt = datetime.datetime.strptime(datestr, '%Y-%m-%d %H:%M:%S') #由字符串到时间对象
print(type(dt), dt)
print(dt.strftime('%Y/%m/%d-%H:%M:%S')) # 输出为字符串
print("{:%Y/%m/%d %H:%M:%S}".format(dt)) # 输出为字符串
```

#### timedelta 类

- datetime2 = datetime1 + timedelta
- datetime2 = datetime1 - timedelta
- timedelta = datetime1 - datetime2
- 构造方法 
  - datetime.timedelta(days=0, seconds=0, microseconds=0, milliseconds=0, minutes=0,hours=0, weeks=0)
  - year = datetime.timedelta(days=365)
- timedelta对象有方法total_seconds()， 返回**时间差的总秒数**

#### time 模块

- time.sleep(secs) 将调用线程挂起指定的秒数

## 偏函数

Python的`functools`模块提供了很多有用的功能，其中一个就是偏函数（Partial function）。要注意，这里的偏函数和数学意义上的偏函数不一样。

在介绍函数参数的时候，我们讲到，通过设定参数的默认值，可以降低函数调用的难度。而偏函数也可以做到这一点。举例如下：

`int()`函数可以把字符串转换为整数，当仅传入字符串时，`int()`函数默认按十进制转换：

```python
>>> int('12345')
12345
```

但`int()`函数还提供额外的`base`参数，默认值为`10`。如果传入`base`参数，就可以做N进制的转换：

```python
>>> int('12345', base=8)
5349
>>> int('12345', 16)
74565
```

假设要转换大量的二进制字符串，每次都传入`int(x, base=2)`非常麻烦，于是，我们想到，可以定义一个`int2()`的函数，默认把`base=2`传进去：

```python
def int2(x, base=2):
    return int(x, base)
```

这样，我们转换二进制就非常方便了：

```python
>>> int2('1000000')
64
>>> int2('1010101')
85
```

`functools.partial`就是帮助我们创建一个偏函数的，不需要我们自己定义`int2()`，可以直接使用下面的代码创建一个新的函数`int2`：

```python
>>> import functools
>>> int2 = functools.partial(int, base=2)
>>> int2('1000000')
64
>>> int2('1010101')
85
```

所以，简单总结`functools.partial`的作用就是，把一个函数的某些参数给固定住（也就是设置默认值），返回一个新的函数，调用这个新函数会更简单。

注意到上面的新的`int2`函数，仅仅是把`base`参数重新设定默认值为`2`，但也可以在函数调用时传入其他值：

```python
>>> int2('1000000', base=10)
1000000
```

最后，创建偏函数时，实际上可以接收函数对象、`*args`和`**kw`这3个参数，当传入：

```python
int2 = functools.partial(int, base=2)
```

实际上固定了int()函数的关键字参数`base`，也就是：

```python
int2('10010')
```

相当于：

```python
kw = { 'base': 2 }
int('10010', **kw)
```

当传入：

```python
max2 = functools.partial(max, 10)
```

实际上会把`10`作为`*args`的一部分自动加到左边，也就是：

```python
max2(5, 6, 7)
```

相当于：

```python
args = (10, 5, 6, 7)
max(*args)
```

结果为`10`。

### **小结**

当函数的参数个数太多，需要简化时，使用`functools.partial`可以创建一个新的函数，这个新函数可以固定住原函数的部分参数，从而在调用时更简单。

