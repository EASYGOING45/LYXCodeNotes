# C++编程思想-泛型编程

- 面向对象是一种通过间接层来调用函数，以换取一种抽象
- 泛型编程则是更直接的抽象，它不会因为间接层而损失效率
- 不同于面向对象的动态期多态，泛型编程是一种静态期多态，通过编译器生成最直接的代码
- 泛型编程可以将算法与特定类型，结构剥离，尽可能复用代码

## 泛型编程实例

```C++
// 模板函数
template<class T>
T maxx(T a, T b)	//A
{
	return a > b ? a:b;
}

//特化
template<>
char* maxx(char* a, char* b)  //B
{
	return (strcmp(a, b) > 0 ?  (a) : (b));
}


template<class T1, class T2>
int maxx(T1 a, T2 b)	//C
{
	return static_cast<int>(a > b ? a : b);
}
```

```C++
// 模板函数的测试
cout << maxx(1, 2) << endl;		//A
cout << maxx(1.5, 3.5) << endl;	//A
cout << maxx('a', 'b') << endl;	//A
cout << maxx("hello", "world") << endl;	//A
char* s1 = "hello";
char* s2 = "world";
cout << maxx(s1, s2) << endl;	//特化 B
cout << maxx(10, 2.5) << endl;	//两个不同类型 C
```

![image-20230105165715105](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105165715105.png)

```C++
// 模板类
template <class T>
class TC
{
public:
	TC(T a, T b,  T c);
	T Min();
	T Max();

private:
	T _a, _b, _c;
};

template<class T>
TC<T>::TC(T a, T b, T c):
	_a(a), _b(b), _c(c)
{
    ;
}

template<class T>
T TC<T>::Min()
{
	T minab = _a < _b ? _a : _b;
	return minab < _c ? minab : _c;
}

template<class T>
T TC<T>::Max()
{
	T maxab = _a < _b ? _b : _a;
	return maxab < _c ? _c : maxab;
}
```

```C++
// 模板类的测试
TC<int> obj1(2, 4, 3);
cout << obj1.Min() << endl;
cout << obj1.Max() << endl;

TC<double> obj2(2.5, 4.4, 3.3);
cout << obj2.Min() << endl;
cout << obj2.Max() << endl;

TC<long> obj3(399950L, 455795L, 333339090L);
cout << obj3.Min() << endl;
cout << obj3.Max() << endl;
```

![image-20230105170522899](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105170522899.png)

## 泛型编程的推理过程

```C++
// 1+2+3...+100 ==> n*(n+1)/2 

template<int n>
struct Sum
{
	enum Value {N = Sum<n-1>::N+n}; // Sum(n) = Sum(n-1)+n
};
template<>
struct Sum<1>
{
	enum Value {N = 1};    // n=1
};

int main()
{
	cout << Sum<100>::N << endl;

    return 0;
}
```

## 小结

模板编程的难点很大程度上在于对编译器的理解，我们需要指导怎么帮助编译器提供需要生成代码的信息。