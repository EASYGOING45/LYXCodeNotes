# STL容器之set/multiset容器

## 概述

set/multiset的特性是所有元素会根据元素的值自动进行排序。set是以RB-tree（红黑树、平衡二叉树的一种）为底层机制，其查找效率非常好。set容器不允许重复元素，multiset允许重复元素。

二叉搜索树，是指二叉树中的节点按照一定的规则进行排序，使得对二叉树中元素访问更加高效。二叉搜索树的放置规则是：任何节点的元素值一定大于其左子树中的每一个节点的元素值，并且小于其右子树的值。

因此从根节点一直向左走，一直到无路可走，即得到最小值；一直向右走，直至无路可走，可得到最大值。

那么在二叉搜索树中找到最大元素和最小元素是非常容易的事情。

![image-20230406191239695](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230406191239695.png)

## set常用API

### 构造函数

```C++
set<T> st;//set默认构造函数：
mulitset<T> mst; //multiset默认构造函数: 
set(const set &st);//拷贝构造函数
```



### 赋值操作

```C++
set& operator=(const set &st);//重载等号操作符
swap(st);//交换两个集合容器
```

### 插入和删除操作

```C++
insert(elem);//在容器中插入元素。
clear();//清除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg, end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(elem);//删除容器中值为elem的元素。

```

### 查找操作

```C++
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回map.end();
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

```