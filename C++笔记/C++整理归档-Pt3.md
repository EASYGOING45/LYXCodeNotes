# C++整理归档-Pt3

## 数组名和指针（这里为指向数组首元素的指针）的区别？

- 二者均可通过增减偏移量来访问数组中的元素
- 数组名不是真正意义上的指针，可以理解为常指针，所以数组名没有自增、自减等操作
- 当数组名当做形参传递给调用函数后，就失去了原有特性，退化成一般指针，多了自增、自建操作，但sizeof运算符不能再得到原数组的大小了

## final和override关键字

### override

当在父类中使用了虚函数时，我们可能需要在某个子类中对这个虚函数进行重写，以下方法均可：

```C++
class A
{
    virtual void foo();
};

class B : public A
{
    void foo();	//可以
    vitrual void foo();	//可以
    void foo() override;	//可以
}
```

倘若没有使用override，我们误将foo()写成了foo()会怎么样？

编译器并不会报错，因为它不知道我们的目的是重写虚函数，而是把它当成了新的函数，如果这个虚函数很重要的话，那就会对整个程序不利，由此体现了override的作用：它制定了子类的某个虚函数是重写的弗雷德，如果名字不小心打错了的话，编译器是不会编译通过的

```C++
class A
{
    virtual void foo();
};
class B : public A
{
    virtual void f00(); //OK，这个函数是B新增的，不是继承的
    virtual void f0o() override; //Error, 加了override之后，这个函数一定是继承自A的，A找不到就报错
};
```

### final

当不希望某个类被继承，或不希望某个虚函数被重写，可以在类名和虚函数后添加final关键字，添加final关键字后被继承或重写的话，编译器会报错，例如：

```C++
class Base
{
    virtual void foo();
};
 
class A : public Base
{
    void foo() final; // foo 被override并且是最后一个override，在其子类中不可以重写
};

class B final : A // 指明B是不可以被继承的
{
    void foo() override; // Error: 在A中已经被final了
};
 
class C : B // Error: B is final
{
};
```

## 拷贝初始化和直接初始化

当用于类类型对象时，初始化的拷贝形式和直接形式有所不同，直接初始化直接调用与实参匹配的构造函数，拷贝初始化总是调用拷贝构造函数。

拷贝初始化首先使用指定构造函数创建一个临时对象，然后用拷贝构造函数将那个临时对象拷贝到正在创建的对象，如下：

```C++
string str1("I am a string");	//语句1，直接初始化
string str2(str1);	//语句2 直接初始化 str1是已经存在的对象，直接调用拷贝构造函数对str2进行初始化
string str3 = "I am a string";	//语句3 拷贝初始化，先为字符串”I am a string“创建临时对象，再把临时对象作为参数，使用拷贝构造函数构造str3
string str4 = str1;	//语句4 拷贝初始化 这里相当于隐式调用拷贝构造函数，而不是调用赋值运算符函数
```

为了提高效率，允许编译器跳过创建临时对象这一步，直接调用构造函数要创建的对象，这样就完全等价于直接初始化了（语句1和语句3等价），但是需要辨别两种情况。

1. 档拷贝构造函数为private时：语句3和语句4在编译时会报错
2. 使用explicit修饰构造函数时，如果构造函数存在隐式转换，编译时会报错

## 初始化和赋值的区别

- 对于简单数据类型来说，初始化和赋值没什么区别

- 对于类和复杂数据类型来说，这两者区别巨大，举例如下：

  ```C++
  class A{
  public:
      int num1;
      int num2;
  public:
      A(int a=0, int b=0):num1(a),num2(b){};
      A(const A& a){};
      //重载 = 号操作符函数
      A& operator=(const A& a){
          num1 = a.num1 + 1;
          num2 = a.num2 + 1;
          return *this;
      };
  };
  int main(){
      A a(1,1);
      A a1 = a; //拷贝初始化操作，调用拷贝构造函数
      A b;
      b = a;//赋值操作，对象a中，num1 = 1，num2 = 1；对象b中，num1 = 2，num2 = 2
      return 0;
  }
  
  ```

## extern "C"的用法

为了能够正确的在C++代码中调用C语言代码，在程序中加上`extern "C"`后，相当于告诉编译器这部分代码是C语言写的，因此要按照C语言标准进行编译，而非C++。

哪些情况需要使用extern "C"：

1. C++代码中调用C语言代码
2. 在C++中的头文件中使用
3. 多人协同开发时，有人写C，有人写C++

举例：

```C++
#ifndef __MY_HANDLE_H__
#define __MY_HANDLE_H__

extern "C"{
    typedef unsigned int result_t;
    typedef void* my_handle_t;
    
    my_handle_t create_handle(const char* name);
    result_t operate_on_handle(my_handle_t handle);
    void close_handle(my_handle_t handle);
}
```

在C语言的的头文件中，对其外部函数只能指定为extern类型，C语言中不支持extern "C"声明，在.c文件中包含了extern "C"时会出现编译语法错误。所以使用extern "C"全部都放在于cpp程序相关文件或其头文件中。

总结如下形式：

1. C++调用C函数

   ```C++
   //xx.h
   extern int add(...)
   
   //xx.c
   int add(){
       
   }
   
   //xx.cpp
   extern "C" {
       #include "xx.h"
   }
   
   ```

2. C调用C++函数

   ```C
   //xx.h
   extern "C"{
       int add();
   }
   //xx.cpp
   int add(){    
   }
   //xx.c
   extern int add();
   
   ```

