# STL容器之Vector数组

## Vector容器

Vector容器是一个长度动态改变的动态数组，既然也是数组，那么其内存是一段连续的内存，具有数组的随机存取的优点。

![image-20230331101933259](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230331101933259.png)

- Vector是动态数组，连续内存空间，具有随机存取效率高的优点
- Vector是单口容器，在队尾插入和删除元素的效率高，在指定位置插入会导致数据元素移动，效率低

> Vector如何实现动态增长？
>
> 当Vector空间满的时候，再当插入新元素的时候，vector会重新申请一块更大的内存空间，将原空间数据拷贝到新的内存空间，然后释放旧的内存空间，再将新元素插入到新空间中，以此可以看出vector的空间动态增长效率较低。

## Vector常用API

### 构造函数

```C++
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int)); 
```

### 赋值操作

```C++
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector& operator=(const vector  &vec);//重载等号操作符
swap(vec);// 将vec与本身的元素互换。

//第一个赋值函数，可以这么写：
int arr[] = { 0, 1, 2, 3, 4 };
assign(arr, arr + 5);//使用数组初始化vector
```

### 大小操作

```C++
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的容量
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问
```

resize 若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。

> **问：reserv和resize的区别?**
>
> **答: reserve是容器预留空间，但在空间内不真正创建元素对象，所以在没有添加新的对象之前，不能引用容器内的元素.**
>
>   **resize****是改变容器的大小，且在创建对象，因此，调用这个函数之后，就可以引用容器内的对象了.**
>
>  **巧用reserve增加程序效率？**

```C++
vector<int> v;
int* p = NULL;
int count = 0;// 统计vector容量增长几次？
for (int i = 0; i < 100000;i++){
	v.push_back(i);
	if (p != &v[0]){
		p = &v[0];
		count++;
	}
}
cout << "count:" << count << endl; //打印出30

```

### 数据存取操作

```C++
at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
operator[];//返回索引idx所指的数据，越界时，运行直接报错
front();//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素
```

### 插入和删除操作

```C++
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele.
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素
```

> vector是个动态数组，当空间不足的时候插入新元素，vector会重新申请一块更大的内存空间，将旧空间数据拷贝到新空间，然后释放旧空间。vector是单口容器，所以在尾端插入和删除元素效率较高，在指定位置插入，势必会引起数据元素移动，效率较低。