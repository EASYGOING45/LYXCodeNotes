# STL容器之Stack栈

## Stack简介

Stack是一种先进后出(first in last out,FILO)的数据结构，它只有一个出口，stack只允许在栈顶新增元素，移除元素，获得顶端元素，但是除了顶端之外，其他地方不允许存取元素，只有栈顶元素可以被外界使用，也就是说stack不具有遍历行为，没有迭代器。

![image-20230402082430362](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230402082430362.png)

- 栈不能遍历，没有迭代器，不支持随机存取，只能通过top从栈顶获取和删除元素

## Stack常用API

### 构造函数

```C++
stack<T> stk;	//stack采用模板类实现
stack(const stack &st);	//拷贝构造函数
```

### 赋值运算

```C++
stack& operator=(const stack &stk);	//重载了等号运算符
```

### 数据存取操作

```C++
push(elem);		//向栈顶添加元素
pop();			//从栈顶移除第一个元素
top();			//返回栈顶元素
```

### 大小操作

```C++
empty();		//判断堆栈是否为空
size();			//返回堆栈的大小
```

