# C++体系构建-Part1

# Day01-C++基础

> 内容整理自《Effective C++》 《C++ Primer第五版》 《C++新经典》等书籍

## 指针与引用

- 指针存放某个对象的地址，其本身就是一个变量（命了名的对象），本身就有一个地址，因此存在`指向指针的指针`
  - 可变
  - 包括其所指向的地址的改变和其指向的地址中所存放的数据的改变
- 引用就是变量的别名，引用不可变，必须初始化

> 不存在指向空值的引用，但是存在指向空值的指针
>
> C11之前使用NULL作为空，NULL来自于C语言
>
> C11之后使用nullptr代表空指针

## const关键字

- const的作用：被const修饰的值不能改变，是只读变量，必须在定义的时候就赋初值

### 常量指针（底层const）

常量指针：是指定义了一个指针，该指针指向一个只读的对象，不能通过常量指针来改变这个对象的值。

常量指针强调的是指针对其所指对象的不可改变性。

特点：靠近变量名

形式：

- const 数据类型* 指针变量 = 变量名
- 数据类型 const *指针变量 = 变量名

```C++
int temp = 10;
const int* a=&temp;	//常量指针
int const *b=&temp;	

//更改操作
*a = 9;	//错误 是只读对象
```

![image-20230105111846420](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105111846420.png)

### 指针常量（顶层const）

指针常量：指针常量是指定义了一个指针，这个指针的值只能在定义时初始化，其他地方不能改变。

指针常量强调的是指针的不可改变性。

特点：靠近变量类型

形式： 数据类型* const 指针变量=变量名

```C++
int temp = 10;
int temp1 = 12;
int* const p = &temp;
cout << *p << endl;

//p = &temp1; //错误 指针常量本身不可改变
*p = 9;
cout << *p << endl; //指针常量指向的值可以改变
```

![image-20230105112843155](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105112843155.png)

## define和typedef的区别

### define

- 知识简单的字符串替换，没有做类型检查
- 是在编译的预处理阶段起作用
- 可以用来防止头文件重复引用
- 不分配内存，给出的是立即数，有多少次使用就进行多少次替换

### typedef

- 有对应的数据类型，是要进行类型检查的
- 在编译、运行期间起作用
- 在静态存储区中分配空间，在程序运行过程中内存中只有一个拷贝

## define和inline的区别

### define

定义预编译时需要处理的宏，只是进行简单的字符串替换，不做类型检查，不安全

### inline

inline是先将内联函数编译完成生成了函数体直接插入被调用的地方，减少了压栈、跳转和返回的操作

inline没有普通函数调用时所产生的额外开销

内联函数是一种特殊的函数，会进行类型检查

内联是一种对编译器的请求，编译器有可能会拒绝这种请求

> C++中对于inline的编译限制：
>
> 1. 不能存在任何形式的循环语句
> 2. 不能存在过多的条件判断语句
> 3. 函数体不能过于庞大
> 4. 内联函数声明必须在调用语句之前

## override和overload

### override是重写（覆盖）了一个方法

override用以实现不同的功能，一般是用于子类在继承父类时，重写父类方法

规则：

1. 重写方法的参数列表，返回值，所抛出的异常与被重写方法一致
2. 被重写的方法不能为private
3. 静态方法不能被重写为非静态方法
4. 重写方法的访问修饰符一定要大于被重写方法的访问修饰符
   - public>protected>default>private

### overload是重载，这些方法的名称相同而参数形式不同

一个方法有着不同的版本，存在于一个类中

规则：

1. 不能通过访问权限、返回类型、抛出的异常进行重载
2. 不同的参数类型可以是不同的参数数据类型、不同的参数个数、不同的参数顺序（参数数据类型必须不一样）
3. 方法的异常类型和数目不会对重载造成影响

> 使用多态是为了避免在父类里大量重载引起代码臃肿且难以维护
>
> 重写与重载的本质区别是：加入了override的修饰符的方法，此方法始终只有一个被你使用的方法

## new和malloc

1. new内存分配失败时，会抛出bac_alloc异常，它不会返回NULL；
   1. malloc分配内存失败时返回NULL
2. 使用new操作符申请内存分配时无需指定内存块的大小
   1. malloc需要显式的指明所需要内存的尺寸
3. operator new/operator delete 可以被重载 而malloc/free不能被重载
4. new/delete会调用对象的构造函数/析构函数以完成对象的构造/析构，而malloc不会
5. malloc与free是C/C++的标准库函数，new/delete则是C++中的运算符
6. new操作符从自由存储区上为对象动态分配内存空间
   1. 而malloc函数则从堆上动态分配内存

![image-20230105142242803](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105142242803.png)

## constexpr和const

- const表示“只读”的语义
  - constexpr表示“常量”的语义
- constexpr只能定义编译期常量，
  - 而const可以定义编译器常量也可以定义运行期常量

如果将一个成员函数标记为constexpr，则顺带也将它标记为了const。

如果将一个变量标记为constexpr，那么同样他也是const的

但相反并不成立

一个const的变量/函数，并不是constexpr的

### constexpr变量

复杂系统中很难分辨一个初始值是不是常量表达式，可以将变量声明为constexpr类型，由编译器来验证变量的值是否是一个常量表达式

`必须使用常量进行初始化`

```C++
constexpr int n = 20;
constexpr int m=n+1;
static constexpr int MOD = 1000000007;
```

如果constexpr声明中定义了一个指针，constexpr仅对指针有效，和所指对象无关

```C++
constexpr int *p=nullptr;	//常量指针 顶层const
const int *q=nullptr;	//指向常量的指针 底层const
int *const q =nullptr;	//顶层const
```

![image-20230105143932938](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105143932938.png)

### constexpr函数

constexpr函数是指能用于常量表达式的函数

函数的返回类型和所有形参类型都是字面值类型，函数体有且只有一条return语句

`constexpr int new() {return 42;}`

为了可以在编译过程展开，constexpr函数被隐式转换成了内联函数。

constexpr和内联函数可以在程序中多次定义，一般定义在头文件

### constexpr构造函数

构造函数不能说const类型

但是字面常量类的构造函数可以是constexpr

constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中，对象调用的成员函数必须使用constexpr修饰

### const

指针常量： `const int* d = new int(2);`  指向常量的一个指针 指向的内容不可变

常量指针：`int *const e = new int(2);`指针自身为常量不可变

区别技巧：左定值，右定向：指的是const在*的左边还是右边 左边：指针常量 右边：常量指针

> 拓展：
>
> 顶层const：指针本身是const
>
> 底层const：指针所指的对象是常量

若要修改const修饰的变量的值，需要加上关键字volatile

若想要修改const成员函数中某些与类状态无关的数据成员，可以使用mutable关键字来修饰这个数据成员

![image-20230105144806744](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105144806744.png)

![image-20230105144639297](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105144639297.png)

### constexpr的好处

1. 为一些不能修改的数据提供保障，写成变量就有被意外修改的风险
2. 有些场景，编译器可以在编译期对constexpr的代码进行优化，提高效率
3. 相比宏来说，没有额外的开销，但是却更加安全可靠