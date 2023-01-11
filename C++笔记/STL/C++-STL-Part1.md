# C++-STL-Part1

## STL（Standard Template Library）

- STL算法是泛型的（generic），不与任何特定数据结构和对象绑定，不必在环境类似的情况下重写代码
- STL算法可以量身定做，并且具有很高的效率
- STL可以进行扩充，可以编写自己的组件并且能与STL标准的组件进行很好的配合

 

![image-20230106114910313](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106114910313.png)

![image-20230106114948870](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106114948870.png)

## 容器（Container)

- 容器用于存放数据；STL的容器分为两大类
- 序列式容器（Sequence Containers）
  - 其中的元素都是可排序的（ordered），STL提供了vector、list、deque等序列式容器，而stack、queue、priority_queue则是容器适配器
- 关联式容器（Associative Containers）
  - 每个数据元素都是由一个键（key）和值（value）组成，
  - 当元素被插入到容器时，按其键以某种特定规则放入适当位置
  - 常见的STL容器如：set、multiset、map、multimap

## 序列式容器实例

```C++
struct Display
{
	//运算符重载 重载（）  相当于函数调用
	void operator()(int i)
	{
		cout << i << " ";
	}
};
```



```C++
int main()
{
	int iArr[] = { 1, 2,3,4,5 };

	vector<int> iVector(iArr, iArr + 4);	//左闭右开 只能取到前4个元素
	list<int> iList(iArr, iArr + 4);		//双向链表
	deque<int> iDeque(iArr, iArr + 4);

	//适配器
	queue<int> iQueue(iDeque);     // 队列 先进先出
	stack<int> iStack(iDeque);         // 栈 先进后出
	priority_queue<int> iPQueue(iArr, iArr + 4);  //优先队列，按优先权 默认值越大越先

	cout << "vector：";
	for_each( iVector.begin(), iVector.end(), Display() );
	cout << endl;

	cout << "list：";
	for_each(iList.begin(), iList.end(), Display());
	cout << endl;

	cout << "deque：";
	for_each(iDeque.begin(), iDeque.end(), Display());
	cout << endl;

	cout << "queue：";
	while ( !iQueue.empty() )
	{
		cout << iQueue.front() << " ";  // 1  2 3 4
		iQueue.pop();
	}
	cout << endl;

	cout << "stack：";
	while (!iStack.empty())
	{
		cout << iStack.top() << " ";    // 4 3  2  1
		iStack.pop();
	}
	cout << endl;

	cout << "priority_queue：";
	while (!iPQueue.empty())
	{
		cout << iPQueue.top() << " "; // 4 3 2 1
		iPQueue.pop();
	}
	cout << endl;
    return 0;
}
```

![image-20230106120934729](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106120934729.png)

## 关联式容器map实例

- map是一种易于查找的容器

- map中的键必须唯一，定义后如果再插入不会改变

- pair结构，组合一个键值结构

- erase：去除，擦除迭代器对应的元素

- 注意迭代器失效问题

  - iter++很关键！！！

  - ```C++
    	iter = studentSocres.begin();
    	while (iter != studentSocres.end())
    	{
    		if (iter->second < 98.0)  // 去除不是优秀的同学
    		{
    			studentSocres.erase(iter++);  // 注意：迭代器失效问题
    		}
    		else
    		{
    			iter++;
    		}
    	}
    ```

    

```C++
struct Display
{
	void operator()(pair<string, double> info)
	{
		cout << info.first << ": " << info.second << endl;
	}
};
```

```C++
	map<string, double> studentSocres;		//定义一个map 类型为 字符串：浮点型
	studentSocres["LiMing"] = 95.0;
	studentSocres["LiHong"] = 98.5;
	studentSocres.insert( pair<string, double>("zhangsan", 100.0) );	//插入操作
	studentSocres.insert(pair<string, double>("Lisi", 98.6));
	studentSocres.insert(pair<string, double>("wangwu", 94.5));
	studentSocres.insert(map<string, double>::value_type("zhaoliu", 95.5) );
	studentSocres["wangwu"] = 88.5;	//修改
	studentSocres.insert(pair<string, double>("wangwu", 94.5));	//不会有任何改动！！！
	for_each(studentSocres.begin(), studentSocres.end(), Display());
	cout << endl;
```

![image-20230106122653483](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106122653483.png)

```C++
	map<string, double>::iterator iter;		//定义迭代器
	iter = studentSocres.find("zhaoliu");	//查找 返回迭代器 如果没有找到的话，返回末尾
	if (iter != studentSocres.end())
	{
		cout << "Found the score is: " << iter->second << endl;
	}
	else
	{
		cout << "Didn't find the key." << endl;
	}
```

![image-20230106122317726](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106122317726.png)

```C++
	// 使用迭代器完成遍历查找的过程
	iter = studentSocres.begin();
	while (iter != studentSocres.end())
	{
		if (iter->second < 98.0)  // 去除不是优秀的同学
		{
			studentSocres.erase(iter++);  // 注意：迭代器失效问题
		}
		else
		{
			iter++;
		}
	}
	for_each(studentSocres.begin(), studentSocres.end(), Display());
	cout << endl;
```

![image-20230106122430954](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106122430954.png)

```C++
	for (iter = studentSocres.begin(); iter != studentSocres.end(); iter++)
	{
		if (iter->second <= 98.5)
		{
			iter = studentSocres.erase(iter);  // 注意：迭代器失效问题
		}
	}
	for_each(studentSocres.begin(), studentSocres.end(), Display());
	cout << endl;

	// find得到并删除元素
	//iter = studentSocres.find("LiHong");
	//studentSocres.erase(iter);
	//for_each(studentSocres.begin(), studentSocres.end(), Display());

	//int n = studentSocres.erase("LiHong1");
	//cout << n << endl;
	//for_each(studentSocres.begin(), studentSocres.end(), Display());

	studentSocres.erase(studentSocres.begin(), studentSocres.end());
	for_each(studentSocres.begin(), studentSocres.end(), Display());
	cout << endl;
```

![image-20230106122853463](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106122853463.png)

## 仿函数

- 仿函数一般不会单独使用，主要是为了搭配STL算法使用
- 函数指针不能满足STL对抽象性的要求，不能满足软件积木的要求，无法和STL其他组件搭配
- 仿函数本质就是类重载了一个operator()，创建一个行为类似函数的对象

### C++方式

```C++
	// C++方式
	bool MySort(int a, int b)
	{
		return a < b;
	}
	void Display(int a)
	{
		cout << a << " ";
	}
	int arr[] = { 4, 3, 2, 1, 7 };
	sort(arr, arr + 5, MySort);		//传递的是C++原生函数
	for_each(arr, arr + 5, Display);
	cout << endl;
```

### C++泛型方式

```C++
// C++泛型
template<class T>
inline bool MySortT(T const& a, T const& b)
{
	return a < b;
}
template<class T>
inline void DisplayT(T const& a)
{
	cout << a << " ";
}

	// C++泛型
	int arr2[] = { 4, 3, 2, 1, 7 };
	sort(arr2, arr2 + 5, MySortT<int>);
	for_each(arr2, arr2 + 5, DisplayT<int>);
	cout << endl;
```

### C++仿函数方式

```C++
// C++仿函数
struct SortF
{
	bool operator() (int a, int b)
	{
		return a < b;
	}
};
struct DisplayF
{
	void operator() (int a)
	{
		cout << a << " ";
	}
};
	// C++仿函数
	int arr3[] = { 4, 3, 2, 1, 7 };
	sort(arr3, arr3 + 5, SortTF<int>() );
	for_each(arr3, arr3 + 5, DisplayTF<int>());
	cout << endl;
```

### C++仿函数模板方式

```C++
// C++仿函数模板
template<class T>
struct SortTF
{
	inline bool operator() (T const& a, T const& b) const
	{
		return a < b;
	}
};

template<class T>
struct DisplayTF
{
	inline void operator() (T const& a) const
	{
		cout << a << " ";
	}
};

	// C++仿函数模板
	int arr4[] = { 4, 3, 2, 1, 7 };
	sort(arr4, arr4 + 5, SortF());
	for_each(arr4, arr4 + 5, DisplayF());
	cout << endl;
```

## 算法（Algorithm）

STL中的算法大致分为四类：包含于`<algorithm>` `<numeric>` `<functional>`

1. 非可变序列算法：指不直接修改其所操作的容器内容的算法
2. 可变序列算法：指可以修改它们所操作的容器内容的算法
3. 排序算法：包括对序列进行排序和合并的算法、搜索算法以及有序序列上的集合操作
4. 数值算法：对容器内容进行数值计算

```C++
	// transform&lambda
	int ones[] = { 1, 2, 3, 4, 5 };
	int twos[] = { 10, 20, 30, 40, 50 };
	int results[5];
	// 数组元素依次相加并返回 开始位置 结束位置 第二个容器（和前一个容器对应个数） 新容器 方法
	transform(ones, ones + 5, twos, results, std::plus<int>()); 
	for_each(results, results + 5,
		[ ](int a)->void {
		cout << a << endl; } ); // lambda表达式（匿名函数）
	cout << endl;
```

![image-20230106144031065](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106144031065.png)

```C++
	// find
	int arr[] = { 0, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7, 7, 8 };
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> iA(arr + 2, arr + 6);   // {2,3,3,4}
	//vector<int> iA;
	//iA.push_back(1);
	//iA.push_back(9); // {1, 9}
	cout << count(arr, arr + len, 6) << endl; // 统计6的个数
	cout << count_if(arr, arr + len, bind2nd(less<int>(),  7) ) << endl; // 统计<7的个数
	cout << binary_search(arr, arr + len, 9) << endl;   // 9找不到
	cout << *search(arr, arr + len, iA.begin(), iA.end()) << endl; // 查找子序列 返回开始的索引
	cout << endl;
	int* a = search(arr, arr + len, iA.begin(), iA.end());
	for_each(a,a+4,
		[](int a)->void
		{
			cout << a << endl;
		});
```

![image-20230106144512984](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106144512984.png)

## 全排列

> 输入一个不存在重复字符的字符串，打印出字符串中字符的全排列。
> 比如：
> 输入: "123"   3*2*1 = 3!
> 输出:  123
> //          132
> //          213
> //          231
> //          321
> //          312
> //f(123) = 1+f(23), f(23) = 2+f(3), f(3)  = 3  递归

递归方式解决

一般方式：

```C++
void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
void Permutation(char* pStr, char* pPostion)
{
	// 基准点 递归终止条件
	if (*pPostion == '\0')
	{
		cout << pStr << endl;
	}
	else
	{
		for (char* pChar = pPostion; *pChar != '\0'; pChar++)
		{
			// 依次和后面的字符交换
			swap(*pChar, *pPostion);

			Permutation(pStr, pPostion + 1);

			// 换回来
			swap(*pChar, *pPostion);
		}
	}
}

	char test[] = "132";
	Permutation(test, test);
	cout << endl;
```

![image-20230106150418956](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106150418956.png)

### STL中的全排列

```C++
	// 用STL输出全排列
	// 注意：必须要保证数组顺序，
	do
	{
		cout << test[0] << test[1] << test[2] << endl;
	} while (next_permutation(test, test + 3));
	cout << endl;

	char test2[] = "321";
	// 注意：必须要保证数组顺序，
	do
	{
		cout << test2[0] << test2[1] << test2[2] << endl;
	} while (prev_permutation(test2, test2 + 3));
```

![image-20230106150454009](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106150454009.png)

STL中的全排列必须按照数组的顺序，输入数组必须有序

## 迭代器（iterator）

- 迭代器是一种smart pointer，用于访问顺序容器和关联容器中的元素，相当于容器和操纵容器的算法之间的中介
- 迭代器本质上是指针
- 迭代器按照定义方式分成以下四种：
  - 正向迭代器 `iterator`
  - 常量正向迭代器（不会修改值） `const_iterator`
  - 反向迭代器 `reverse_iterator`
  - 常量反向迭代器 `const_reverse_iterator`
- ![image-20230106151434527](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106151434527.png)

```C++
	list<int> v;
	v.push_back(3);
	v.push_back(4);
	v.push_front(2);
	v.push_front(1);  // 1, 2, 3, 4

	list<int>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		//*it += 1;	const_iterator不允许修改值
		cout << *it << " ";
	}
	cout << endl;
```

![image-20230106151636070](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106151636070.png)

```C++
	cout <<v.front() << endl;
	v.pop_front();  // 从顶部去除

	list<int>::reverse_iterator it2;
	for (it2 = v.rbegin(); it2 != v.rend(); it2++)
	{
		*it2 += 1;
		cout << *it2 << " ";                          // 5 4 3
	}
	cout << endl;
```

![image-20230106152106424](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106152106424.png)

## 手写GC与异常

```C++
// MyGC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GCPtr.h"

int main()
{
	GCPtr<int> p;	//垃圾回收指针

	try {
		p = new int;
	}
	catch (bad_alloc exc){
		cout << "Allocation failure!\n";
		return 1;
	}
	*p = 88;
	*p += 1;
	cout << "Value at p is: " << *p << endl;
	cout << "p's list size: " << p.gclistSize() << endl;
	GCPtr<int> p1 = p;
	cout << "p's list size: " << p.gclistSize() << endl;
	p.showlist();

	GCPtr<int, 10> pA = new int[10];
	Iter<int> it = pA.begin();
	int index = 1;
	for (; it != pA.end(); it++)
	{
		*it = index++;
	}
	it = pA.begin();

	for (; it != pA.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "pA's list size: " << pA.gclistSize() << endl;
	it = pA.begin();
	cout << *(it) << endl;
	cout << *(++it) << endl;
	pA.showlist();

	return 0;
}

//!!! 自定义迭代器必须提供iterator_traits的五种特性，分别是迭代器类型、元素类型、距离类型、指针类型与reference类型!!!
//template<class Iterator>
//struct iterator_traits
//{
//	typedef typename Iterator::difference_type difference_type;
//	typedef typename Iterator::value_type value_type;
//	typedef typename Iterator::pointer pointer;
//	typedef typename Iterator::reference reference;
//	typedef typename Iterator::iterator_category iterator_category;
//}；
```

![image-20230106153319372](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106153319372.png)

## 容器适配器（adapter）

- stack 堆栈
  - 一种先进后出的容器，底层数据结构使用的是deque
- queue 队列
  - 一种先进先出的容器 底层数据结构使用的是deque
- priority_queue 优先队列 默认是最大值优先
  - 一种特殊的队列，它能够在队列中进行排序（堆排序），底层实现结构是vector/deque

```C++
	priority_queue<int> pq;  // 默认是最大值优先
	priority_queue<int, vector<int>, less<int> > pq2; //   最大值优先
	priority_queue<int, vector<int>, greater<int> > pq3; // 最小值优先

	pq.push(2);
	pq.push(1);
	pq.push(3);
	pq.push(0);
	while (!pq.empty())
	{
		int top = pq.top();
		cout << " top is: " << top<< endl;
		pq.pop();
	}
	cout << endl;


	pq2.push(2);
	pq2.push(1);
	pq2.push(3);
	pq2.push(0);
	while (!pq2.empty())
	{
		int top = pq2.top();
		cout << " top is: " << top << endl;
		pq2.pop();
	}
	cout << endl;


	pq3.push(2);
	pq3.push(1);
	pq3.push(3);
	pq3.push(0);
	while (!pq3.empty())
	{
		int top = pq3.top();
		cout << " top is: " << top << endl;
		pq3.pop();
	}
	cout << endl;
```

![image-20230106154845939](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106154845939.png)

## 空间配置器（allocator）

- 从使用的角度来看，allocator隐藏在其他组件中默默工作，不需要关心
- 但是从理解STL实现的角度来看，它是需要首先分析的组件
- allocator的分析可以体现C++在性能和资源管理上优化的思想

JJalloc

```C++
#pragma once
#ifndef _JJALLOC
#define _JJALLOC
#include<new> //for placement new
#include<cstddef> //for ptrdiff_t ,size_t
#include<cstdlib> //for exit()
#include<climits> //for UINX_MAX
#include<iostream> //for cerr

namespace  JJ
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)		//分配空间
	{
		set_new_handler(0);	//告知系统如何处理异常
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);

	}

	template<class T1, class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new(p) T1(value);//placement new,invoke constuctor of T1
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class T>
	class allocator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		//rebind allocator of type U
		template<class U>
		struct rebind {
			typedef allocator<U> other;
		};
		//需要加上以下2个函数，windows的编译器用到了allocator不同类型的拷贝， 
		allocator()
		{
			return;
		}

		template <class U>
		allocator(const allocator<U>& c)
		{
		}

		//hint user for locality,第2个参数是个提示，实现上可能会利用它来增进区域性（locality），或完全忽略之
		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T& value)
		{
			_construct(p, value);
		}
		void destroy(pointer p)
		{
			_destroy(p);
		}
		pointer address(reference x) { return (pointer)&x; }
		const_pointer const_address(const_reference x) { return (const_pointer)&x; }

		size_type max_size() const {
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}//#end of namespace JJ
#endif
```

![image-20230106160449130](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230106160449130.png)

## STL小结

- STL的六大组件给软件编程带来了新的多态和复用，是现代C++语言高效的精髓