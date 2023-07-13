# C++11新标准-Part3

## 7、说说你了解的auto_ptr的作用

1. `auto_ptr`的出现，主要是为了解决有异常抛出时发生内存泄漏的问题，抛出异常，将导致指针p所事项的空间得不到释放儿导致内存泄漏
2. auto_ptr构造时取得某个对象的控制权，在析构时释放该对象。我们实际上是创建一个auto_ptr<Type>类型的局部对象，该局部对象析构时，会将自身所拥有的指针空间释放，所以不会有内存泄漏；
3. auto_ptr的构造函数是explicit，阻止了一般指针隐式转换为 auto_ptr的构造，所以不能直接将一般类型的指针赋值给auto_ptr类型的对象，必须用auto_ptr的构造函数创建对象；
4. 由于auto_ptr对象析构时会删除它所拥有的指针，所以使用时避免多个auto_ptr对象管理同一个指针；
5. Auto_ptr内部实现，析构函数中删除对象用的是delete而不是delete[]，所以auto_ptr不能管理数组；
6. auto_ptr支持所拥有的指针类型之间的隐式类型转换。
7. 可以通过*和->运算符对auto_ptr所有用的指针进行提领操作；
8. T* get(),获得auto_ptr所拥有的指针；T* release()，释放auto_ptr的所有权，并将所有用的指针返回

## 8、智能指针的循环引用

循环引用是指使用多个智能指针 shared_ptr时，出现了指针之间相互指向，从而形成环的情况，有点类似于死锁，这种情况下，智能指针往往不能正常调用对象的析构函数，从而造成内存泄漏。如下例：

```C++
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	Node(const T& value)
		:_pPre(NULL)
		, _pNext(NULL)
		, _value(value)
	{
		cout << "Node()" << endl;
	}
	~Node()
	{
		cout << "~Node()" << endl;
		cout << "this:" << this << endl;
	}

	shared_ptr<Node<T>> _pPre;
	shared_ptr<Node<T>> _pNext;
	T _value;
};

void Funtest()
{
	shared_ptr<Node<int>> sp1(new Node<int>(1));
	shared_ptr<Node<int>> sp2(new Node<int>(2));

	cout << "sp1.use_count:" << sp1.use_count() << endl;
	cout << "sp2.use_count:" << sp2.use_count() << endl;

	sp1->_pNext = sp2; //sp2的引用+1
	sp2->_pPre = sp1; //sp1的引用+1

	cout << "sp1.use_count:" << sp1.use_count() << endl;
	cout << "sp2.use_count:" << sp2.use_count() << endl;
}
int main()
{
	Funtest();
	system("pause");
	return 0;
}
//输出结果
//Node()
//Node()
//sp1.use_count:1
//sp2.use_count:1
//sp1.use_count:2
//sp2.use_count:2
```

从上面shared_ptr的实现中我们知道了只有当引用计数减减之后等于0，析构时才会释放对象，而上述情况造成了一个僵局，那就是析构对象时先析构sp2,可是由于sp2的空间sp1还在使用中，所以sp2.use_count减减之后为1，不释放，sp1也是相同的道理，由于sp1的空间sp2还在使用中，所以sp1.use_count减减之后为1，也不释放。sp1等着sp2先释放，sp2等着sp1先释放,二者互不相让，导致最终都没能释放，内存泄漏。

在实际编程过程中，应该尽量避免出现智能指针之前相互指向的情况，如果不可避免，可以使用使用弱指针——weak_ptr，它不增加引用计数，只要出了作用域就会自动析构。

## 9、手写实现智能指针类需要实现哪些函数？

- 智能指针是一个数据类型，一般用模板实现，模拟指针行为的同时还会提供自动地垃圾回收机制。它会自动记录 `SmartPointer<T*>`对象的引用计数，一旦T类型对象的引用计数为0，就释放该对象

  除了指针对象外，我们还需要一个引用计数的指针设定对象的值，并将引用计数计为1，需要一个构造函数。新增对象还需要一个构造函数，析构函数负责引用计数减少和释放内存。

  通过覆写赋值运算符，才能将一个旧的智能指针赋值给另一个指针，同时旧的引用计数减1，新的引用计数加1

- 一个构造函数、拷贝构造函数、复制构造函数、析构函数、移动函数；

## 10、智能指针出现循环引用时如何解决？

弱指针weak_ptr专门用于解决shared_ptr的循环引用问题，weak_ptr不会修改引用计数，即其存在与否并不影响对象的引用计数器。

循环引用就是：两个对象互相使用一个shared_ptr成员变量指向对方。弱引用并不对对象的内存进行管理，在功能上类似于普通指针，然而一个比较大的区别是，弱引用能检测到所管理的对象是否已经被释放，从而避免访问非法内存。