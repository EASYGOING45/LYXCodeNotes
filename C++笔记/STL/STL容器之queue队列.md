# STL容器之queue队列

## queue简介

queue是一种先进先出(first in first out, FIFO)的数据类型,他有两个口，数据元素只能从一个口进，从另一个口出.队列只允许从队尾加入元素，队头删除元素，必须符合先进先出的原则，queue和stack一样不具有遍历行为。

![image-20230402083007415](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230402083007415.png)

- 先进先出，一个入口，一个出口
- 不能随机存取，不支持遍历

## queue常用API

### 构造函数

```C++
queue<T> que;	//模板类实现
queue(const queue &que);	//拷贝构造函数
```

### 存取、插入、删除操作

```C++
push(elem);	//向队尾添加元素
pop();	//从队头移除第一个元素
back();	//返回最后一个元素
front();	//返回第一个元素
```

### 赋值操作

```C++
queue &operator=(const queue &que);	//重载等号运算符
```

### 大小操作

```C++
empty();	//判断队列是否为空
size();		//返回队列的大小
```

