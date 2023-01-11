# C++体系构建-Part2

## void*，NULL和nullptr

> void *可以说是万能指针

- 在C语言中

  - `define NULL((void *)0)`

- 在C++中

  - ```C++
    #ifndef NULL
    	#ifdef __cplusplus
    		#define NULL 0
    	#else
    		#define NULL((void *)0)
    	#endif
    #endif
    ```

- 在C++11中，nullptr用来替代(void*)0，NULL则只表示0

```C++
void func(void* i)
{
	cout << "func(void* i)" << endl;
}
void func(int i)
{
	cout << "func(int i)" << endl;
}

int main()
{
	int* pi = NULL;
	int* pi2 = nullptr;
	char* pc = NULL;
	char* pc2 = nullptr;
	func(NULL);                   // func(int i)
	func(nullptr);                 // func(void* i)
	func(pi);                         // func(void* i)
	func(pi2);                       // func(void* i)
	func(pc);                        // func(void* i)
	func(pc2);                      // func(void* i)
    return 0;
}
```

![image-20230105160110181](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105160110181.png)

## C中的类型转换

- C类型转换：
  - 隐式类型转换
    - `double f=1.0/2;`
  - 显式类型转换
    - `(类型说明符)(表达式)`
    - `double f = double(1) / double(2);`
- C类型转换存在的问题
  - 任意类型之间都可以转换，编译器无法判断其正确性
  - 难以定位，在源码中无法快速定位

## C++中的类型转换

- const_cast

  - 用于转换指针或引用，可以去掉类型的const属性

  - ```C++
    // C++ const_cast
    const int a = 10;
    //int* pA = &a;	//error
    int* pA = const_cast<int*>(&a);
    *pA = 100;
    ```

- reinterpret_cast  很危险

  - 重新解释类型 既不检查指向的内容 也不检查指针类型本身

  - 但要求转换前后的类型所占用内存大小一致，否则将引发编译时的错误

  - ```C++
    int Test()
    {
    	return 0;
    }
    
    // C++ reinterpret_cast	
    typedef void(*FuncPtr) ();	//定义一个函数指针  返回值为void 参数也为void的函数的函数指针
    FuncPtr funcPtr;
    //funcPtr = &Test; error 类型不一 得强转
    funcPtr = reinterpret_cast<FuncPtr>(&Test);	//转换不同类型的函数指针
    ```

- static_cast

  - 用于基本类型转换 有继承关系类对象和类指针之间的转换

  - 由程序员来确保转换是安全的，他不会产生动态转换的类型安全检查的开销

  - ```C++
    // static_cast
    int i = 6;
    double d = static_cast<double>(i);                  //基本类型转换  int -> double
    double d2 = 5.6;
    int i2 = static_cast<int>(d2);                            //基本类型转换  double -> int
    ```

    ![image-20230105162022841](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105162022841.png)

- dynamic_cast

  - 只能用于含有虚函数的类 必须用在多态体系中

  - 用于类层次间的向上和向下转换

  - 向下转换时，如果是非法的对于指针返回NULL

  - ```C++
    class Base
    {
    public:
    	Base() : _i(0) { ; }
    	virtual void T() { cout << "Base:T" << _i << endl; }
    private:
    	int _i;
    };
    
    class Derived : public Base
    {
    public:
    	Derived() :_j(1) { ; }
    	virtual void T() { cout << "Derived:T" << _j << endl; }
    
    private:
    	int _j;
    };
    ```

    

  - ```C++
    // 子类--》 父类 安全
    	pcb = static_cast<Base*>(&cd);
    	pcb->T();
    	if (pcb == NULL)
    	{
    		cout << "1:unsafe dynamic_cast from Derived to Base" << endl;
    	}
    	pcb = dynamic_cast<Base*>(&cd);
    	pcb->T();
    	if (pcb == NULL)
    	{
    		cout << "2:unsafe dynamic_cast from Derived to Base" << endl;
    	}
    
    	// 父类--》 子类
    	pcd = static_cast<Derived*>(&cb);
    	pcd->T();
    	if (pcd == NULL)
    	{
    		cout << "3:unsafe dynamic_cast from Derived to Base" << endl;
    	}
    
    	pcd = dynamic_cast<Derived*>(&cb);	//不安全 会报错
    	pcd->T();
    	if (pcd== NULL)
    	{
    		cout << "4:unsafe dynamic_cast from Derived to Base" << endl;
    	}
    ```

    

  ![image-20230105162730946](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105162730946.png)

## volatile

定义：与const绝对对立，是类型修饰符	

影响编译器编译的结果，用volatile关键字声明的变量表示该变量随时可能发生变化，与该变量有关的运算，不要进行编译优化

会从内存中重新装在内容，而不是直接从寄存器种拷贝内容

作用：指令关键字，确保本条指令不会因为编译器的优化而省略，且要求每次直接读值，保证对特殊地址的稳定访问

使用场合：在中断服务程序和CPU相关寄存器的定义

举例：

空循环：`for(volatile int i=0;i<100000;i++);	//它会执行 而不是会被优化掉`

## extern

定义：声明外部变量（在函数或者文件外部定义的全局变量）

## static

作用：实现多个对象之间的数据共享和隐藏，并且使用静态成员不会破坏隐藏规则 static变量默认初始化为0

## 前置++与后置++

```C++
self &operator++() {
 	node = (linktype)((node).next);
 	return *this;
}
const self operator++(int) {
 	self tmp = *this;
 	++*this;
 	return tmp;
 }
```

为了区分前后置，重载函数是以参数类型来区分，在调用得到时候，编译器默默给int指定为1个0

### 为什么后置++返回对象，而不是引用？

因为后置++为了返回旧值创建了一个临时对象，在函数结束的时候这个对象就会被销毁，如果返回引用，那么对象都已经销毁了，引用不了。

### 为什么后置前面也要加const

也可以不加，但是为了防止使用i++++，连续两次调用后置++重载符

原因：

它与内置类型行为不一样，无法获得期望的结果

因为第一次返回的是旧值，而不是原对象

若调用两次后置++，结果实际上只累加了一次，所以我们必须手动禁止其合法化，所以要在前面加上const

### 处理用户的自定义类型

最好使用前置++，因为他不会创建临时对象，进而不会带来构造和析构而造成的额外开销

### std::atomic

问题：a++和int a=b 在C++种是否是线程安全的？

答案：不安全

### 例1

a++:从C/C++语法的级别来看，这是一条语句，应该是原子的，但从编译器得到的汇编指令来看，其实不是原子的，

其一般对应三条指令，首先将变量a对应的内存值搬运到某个寄存器中（如eax），然后将该寄存器中的值自增1，再将该寄存器中的值搬运回a代表的内存中

```
mov eax,dword ptr [a] # (1)
inc eax #(2)
mov dword ptr [a],eax #(3)
```

现在假设i的值为0，有两个线程，每个线程对变量a的值都递增1，预想⼀下，其结果应该是 2，可实际运⾏结构可能是1！是不是很怪？

```C++
int a = 0;
// 线程1（执⾏过程对应上⽂汇编指令(1)(2)(3)）
void thread_func1() {
	a++;
}
// 线程2（执⾏过程对应上⽂汇编指令(4)(5)(6)）
void thread_func2() {
	a++;
}
```

我们预想的结果是线程1和线程2的三条指令ݱ自执⾏，最终a的值变为2，但是由于操作系统 线程调度的不确定性，线程1执⾏完指令(1)和(2)后，eax寄存器中的值变为1，此时操作系统ڔ 换到线程2执⾏，执⾏指令(3)(4)(5)，此时eax的值变为1；接着操作系统ڔ回线程1继续执⾏， 执⾏指令(6)，得到a的最终结果1。

### 例2

int a = b; 从C/C++语法的级别来看，这是条语句应该是原⼦的；但从编译器得到的汇编 指令来看，由于现在计算机CPU架构体系的限制，数据不能直接从内存某处搬运到内存另外 ⼀处，必须借助寄存器中转，因此这条语句⼀般对应两条计算机指令，即将变量b的值搬运到 某个寄存器（如eax）中，再从该寄存器搬运到变量a的内存地址中：

```
mov eax, dword ptr [b]
mov dword prt [a], eax
```

既然是两条指令，那么多个线程在执⾏这两条指令时，某个线程可能会在第⼀条指令执⾏完毕 后被剥夺CPU时间⽚，ڔ换到另⼀个线程⽽出现不确定的情况.

### 解决方法：

C++11新标准发布后改变了这种困境，新标准提供了对于整型变量原子操作的相关库，即std::atomic，这是一个模板类型：

```C++
template<class T>
struct atomic;
```

我们可以传⼊具体的整型类型对模板进⾏实例化，实际上stl库也提供了这些实例化的模板类型

```C++
// 初始化1
std::atomic<int> value;
value = 99;
// 初始化2
// 下⾯代码在Linux平台上⽆法编译通过（指在gcc编译器）
std::atomic<int> value = 99;
// 出错的原因是这⾏代码调⽤的是std::atomic的拷⻉构造函数
// ⽽根据C++11语⾔规范，std::atomic的拷⻉构造函数使⽤=delete标记禁⽌编译器⾃动⽣成
// g++在这条规则上遵循了C++11语⾔规范
```

