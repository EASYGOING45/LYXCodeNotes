# C++复盘-基础语法-Ⅱ

### Static关键字

修饰局部变量：静态存储区（全局数据区）分配内存；首次函数调用中初始化，之后的函数调用不再初始化，局部作用域内可见

修饰全局变量：静态存储区（全局数据区）分配内存，整个文件内可见，文件外不可见

修饰函数：整个文件可以，文件外不可见，避免函数同名冲突（static修饰函数的弊端：仅在本文件内可见）

修饰成员变量：所有对象共享，类外初始化，不需要对象实例化就可以访问

修饰成员函数：所不能访问非静态成员（变量，不能调用非静态成员函数）原因是不能接受this指针，与任何对象无关，只能访问静态成员，不需要对象实例化就可以访问

C和C++中的区别：C中只能修饰局部变量和全局变量、函数，C++中的const还能修饰成员变量和成员函数

### inline关键字

- inline必须和定义放在一起，和声明放在一起不起作用

  ```C++
  //如下风格的函数Foo 不能成为内联函数
  inline void Foo(int x,int y);	//inline 仅与函数声明放在一起
  void Foo(int x,int y)
  {    
  }
  
  //而如下风格的函数Foo 则成为内联函数
  void Foo(int x,int y);
  inline void Foo(int x,int y) //inline 与函数定义体放在一起
  {
  }
  ```

  

- 定义在类声明之中的成员函数将自动地成为内联函数

- 内联声明只是建议，是否内联由编译器决定，实际不可控

- 递归函数（自己调用自己的函数）是不能被用来做内联函数的

- 优点：

  - 调用地方展开，省去调用时间，提高效率
  - 相比#define宏函数，代码展开时会进行语法安全检查或数据类型转换，更加安全

- 缺点：

  - 代码膨胀，开销大
  - 如果内联函数本身执行时间长，效率提升就会比较小
  - 修改内联函数，所有调用内联函数的文件必须重新编译

### virtual虚函数可以是inline内联函数吗

虚函数可以是内联函数，但是当虚函数表现多态的时候不能内联，内联是在编译期间进行内联，多态是在运行期间，编译器无法直到调用哪个代码

### 内联函数和宏的区别

- 内联函数：
  - 编译阶段
  - 本身是函数，会进行类型检查，更安全
  - 内联函数有作用域和访问权限（private等）
- 宏：
  - 预处理阶段
  - 本身不是函数，不仅限于类型检查，简单的替换
  - 宏没有限定的作用域和访问权限
  - assert是宏不是函数

### const

- 常量指针、指针常量
  - 常量指针
    - 常量是指针？ ×
    - 所以不能用这个指针修改变量值，原来的声明可以修改值
    - const * 常量 指针
  - const int *p
  - int const *p
  - 指针常量
    - 指针是常量？ √
    - 所以指针指向的东西不能改变：指向哪个变量就是哪个，不能修改
    - *const 指针 常量
  - int *const p
- 悬挂指针和野指针？
  - 悬挂指针：指针所指对象已经被释放
  - 野指针：未初始化的指针
  - 如何避免野指针？ 初始化时指向NULL、释放之后指向NULL
- 顶层const、底层const
  - 顶层：修饰指针（指针常量），指向不可变，指向的变量内容可变
  - 底层：修饰变量（常量指针）
  - 从右往左读变量声明，先修饰左边，左边没有

- const函数
  - 变量：const函数承诺内部不会修改成员变量(multable)
  - 函数：const函数只能调用const函数，非const函数可以调用const函数
  - 类体外定义的声明和定义处都需要写const
  - 如果const构成函数重载，const对象只能调用const函数，非const对象优先调用非const函数

### #define的作用

- 定义标识、定义常数、定义函数
- 提高速度，易读性增强

### const和#define的区别

- 编译器处理方式不同：#define是预处理阶段展开；const是编译阶段使用
- 类型和安全检查不同：#define没有类型，不做任何检查；const编译阶段会执行检查
- 存储方式不同：#define代码展开，多个地方进行替换，不会分配内存；const分配内存，只维持一份拷贝
- 定义域不同：#define不受定义域限制；const只在定义域内有效

### typedef和define区别

|          | typedef                    | define                                                       |
| -------- | -------------------------- | ------------------------------------------------------------ |
| 用法     | 定义数据类型的别名         | 定义常量以及宏                                               |
| 执行时间 | 编译时处理，有类型检查功能 | 预编译时期，不检查，只是替换，编译时侯展开运行发生错误才会报错 |
| 作用域   | 有作用域限定               | 不受作用域约束，define声明后的引用都正确                     |
| 指针     | typedef int*               |                                                              |

### #ifdef、#else、#endif、#ifndef

- 条件编译：对一部分内容指定编译条件

  ```C++
  函数内部编译某些程序段
  #ifdef 条件
      	程序段
  #else
      	程序段
  #endif
  ```

- 用if语句也能达到要求，但是编译了所有语句；条件编译可以减少被编译的语句

  ```C++
  避免头文件重定义
  #ifndef CLASSA_H
  $define CLASSA_H
  ...
  #endif
  ```

  
