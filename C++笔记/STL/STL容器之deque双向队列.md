# STL容器之deque双向队列

## deque概述

deque是“double-ended queue”的缩写,和vector一样，deque也支持随机存取。vector是单向开口的连续性空间，deque则是一种双向开口的连续性空间，所谓双向开口，意思是可以在头尾两端分别做元素的插入和删除操作，vector当然也可以在头尾两端进行插入和删除操作，但是头部插入和删除操作效率奇差，无法被接受。

![image-20230401080112198](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230401080112198.png)

- 双端插入和删除元素效率较高
- 指定位置插入也会导致数据元素移动，降低效率
- 可随机存取，效率高

## deque常用API

### 构造函数

```C++
deque<T> deqT;//默认构造形式
deque(beg, end);//构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n, elem);//构造函数将n个elem拷贝给本身。
deque(const deque &deq);//拷贝构造函数
```

### 赋值操作

```C++
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
deque& operator=(const deque &deq); //重载等号操作符 
swap(deq);// 将deq与本身的元素互换
```

### 大小操作

```C++
deque.size();	//返回容器中元素的个数
deque.empty();	//判断容器是否为空
deque.resize(num);	//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num, elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除。
```

### 双端插入和删除操作

```C++
push_back(elem);	//在容器尾部添加一个数据
push_front(elem);	//在容器头部插入一个数据
pop_back();			//删除容器最后一个数据
pop_front();		//删除容器第一个数据
```

### 数据存取

```C++
at(idx);		//返回索引idx所指的数据，如果越界，抛出out of range
operator[];		//返回索引idx所指的数据，如果越界，抛出out of range
front();		//返回第一个数据
back();			//返回最后一个数据
```

### 插入操作

```C++
insert(pos,elem);		//在pos位置插入一个elem元素的拷贝，返回新数据的位置
insert(pos,n,elem);		////在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);	////在pos位置插入[beg,end)区间的数据，无返回值。
```

> deque是分段连续的内存空间，通过中控器维持一种连续内存空间的状态，其实现复杂性要大于vector queue stack等容器，其迭代器的实现也更加复杂，在需要对deque容器元素进行排序的时候，建议先将deque容器中数据数据元素拷贝到vector容器中，对vector进行排序，然后再将排序完成的数据拷贝回deque容器。

### 删除操作

```C++
clear();	//移除容器的所有数据
erase(beg,end);	//删除[beg,end]区间的数据，返回下一个数据的位置
erase(pos);		//删除pos位置的数据，返回下一个数据的位置。
```

