# STL容器之map/multimap容器

## 简介

map相对于set而言，map具有键值和实值，所有元素根据键值自动排序。pair的第一元素被称为键值，第二元素被称为实值。map也是以红黑树为底层实现机制。

> 可以通过map的迭代器修改map的键值吗？
>
> ​	答案是否定的，键值关系到容器内元素的排列规则，任意改变键值会破坏容器的排列规则，但是你可以改变实值。

map和multimap的区别在于，map不允许相同key值存在，multimap允许相同key值存在。

## 对组

对组（pair）将一对值组合成一个值，这一对值可以具有不同的数据类型，两个值可以分别用pair的两个公有函数first和second访问。

类模板：template <class T1,class T2> struct pair。

如何创建对组？

```C++
//第一种方法创建一个对组
pair<string, int> pair1(string("name"), 20);
cout << pair1.first << endl; //访问pair第一个值
cout << pair1.second << endl;//访问pair第二个值
//第二种
pair<string, int> pair2 = make_pair("name", 30);
cout << pair2.first << endl;
cout << pair2.second << endl;
//pair=赋值
pair<string, int> pair3 = pair2;
cout << pair3.first << endl;
cout << pair3.second << endl;
```

## map常用API

### 构造函数

```C++
map<T1, T2> mapTT;//map默认构造函数: 
map(const map &mp);//拷贝构造函数
```

### 赋值操作

```C++
map& operator=(const map &mp);//重载等号操作符
swap(mp);//交换两个集合容器
```

### 大小操作

```C++
size();//返回容器中元素的数目
empty();//判断容器是否为空
```

### 插入数据元素操作

```C++
map.insert(...); //往容器插入元素，返回pair<iterator,bool>
map<int, string> mapStu;
// 第一种 通过pair的方式插入对象
mapStu.insert(pair<int, string>(3, "小张"));
// 第二种 通过pair的方式插入对象
mapStu.inset(make_pair(-1, "校长"));
// 第三种 通过value_type的方式插入对象
mapStu.insert(map<int, string>::value_type(1, "小李"));
// 第四种 通过数组的方式插入值
mapStu[3] = "小刘";
mapStu[5] = "小王";
```

- 前三种方法，采用的是insert()方法，该方法返回值为pair<iterator,bool>
- 第四种方法非常直观，但存在一个性能的问题。插入3时，先在mapStu中查找主键为3的项，若没发现，则将一个键为3，值为初始化值的对组插入到mapStu中，然后再将值修改成“小刘”。若发现已存在3这个键，则修改这个键对应的value。
- string strName = mapStu[2];  //取操作或插入操作

只有当mapStu存在2这个键时才是正确的取操作，否则会自动插入一个实例，  键为2，值为初始化值。

### 删除操作

```C++
clear();//删除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg,end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(keyElem);//删除容器中key为keyElem的对组。
```

### 查找操作

```C++
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
lower_bound(keyElem);//返回第一个key<=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
```