# C++体系构建-Part4

## 空类

1. 为何空类的大小不是0？

   1. 为了确保两个不同对象的地址不同，所以大小必须不能是0

   2. 类的实例化是在内存中分配一块地址，每个实例在内存中都有着独一无二的地址

   3. 同样，空类也会实例化，所以编译器会给空类隐含的添加一个字节，这样空类实例化后就有独一无二的地址

   4. 所以，空类的sizeof为1，而不是0

   5. ```C++
      class A{ virtual void f(){} };
      class B:public A{}
      ```

   6. 此时，类A和类B都不是空类，其sizeof都是4，因为它们都具有虚函数表的地址

   7. 

   8. ```C++
      class A{};
      class B:public virtual A{}；
      ```

   9. 此时，A是空类，B不是空类，B的大小为4，因为其还有指向虚基类的指针

   10. 多重继承的空类的大小也是1

   11. ```C++
       class Father1{}; class Father2{};
       class Child:Father1, Father2{};
       ```

   12. 它们的sizeof都是1

2. 何时共享虚函数地址表：

   1. 如果派生类继承的第一个是基类，且该基类定义了虚函数地址表，则派生类就共享该表首址占用的存储单元
   2. 对于除前述情形以外的其他任何情形，派生类在处理完所有基类或虚基类后，根据派生类是否建立了虚函数地址表，确定是否为该表首址分配存储单元

3. ```C++
   class X{}; //sizeof(X):1
   class Y : public virtual X {}; //sizeof(Y):4 有指向虚基类的指针
   class Z : public virtual X {}; //sizeof(Z):4 有指向虚基类的指针
   class A : public virtual Y {}; //sizeof(A):8 有2个指向虚基类的指针
   class B : public Y, public Z{}; //sizeof(B):8
   class C : public virtual Y, public virtual Z {}; //sizeof(C):12
   class D : public virtual C{}; //sizeof(D):16
   ```

## 抽象类与接口的实现

接口描述了类的行为和功能，而不需要完成类的特定实现

C++接口是使用抽象类来实现的

1. 类中至少有一个函数被声明为纯虚函数，则这个类就是抽象类

   1. 纯虚函数是通过在声明中使用 `=0`来指定的

2. 设计抽象类（通常称为ABC）的目的，是为了给其他类提供一个可以继承的适当的基类。

   1. 抽象类不能被用于实例化对象，它只能作为接口使用

3. ```C++
   class Shape
   {
   public:
    	// 提供接⼝框架的纯虚函数
    	virtual int getArea() = 0;
   	 void setWidth(int w)
    	{
   		 width = w;
    	}
    	void setHeight(int h)
   	 {
   		 height = h;
   	 }
   protected:
    	int width;
   	 int height;
   };
   
   // 派⽣类
   class Rectangle: public Shape
   {
   public:
   	 int getArea()
    	{
    		return (width * height);
   	 }
   };
   
   class Triangle: public Shape
   {
   public:
   	 int getArea()
   	 {
   		 return (width * height)/2;
   	 }
   };
   ```

   ```C++
   Rectangle Rect;
   Triangle Tri;
   Rect.setWidth(5);
   Rect.setHeight(7);
   Rect.getArea(); //35
   Tri.setWidth(5);
   Tri.setHeight(7);
   Tri.getArea(); //17
   ```

   

## 智能指针

### shared_ptr

1. shared_ptr的实现机制是在拷贝构造时使用同一份引用计数

   1. 一个模板指针 `T* ptr` 指向实际的对象
   2. 一个引用次数 必须是new出来的，否则多个 shared_ptr里面会有不同的引用次数而导致多次delete
   3. 重载 `operator*`和 `operator->` 使得其能够像指针一样使用shared_ptr
   4. 重载 `copy constructor` 使其引用次数加1 （拷贝构造函数）
   5. 重载 `operator=` 赋值运算符 如果原来的shared_ptr已有对象，则让其引用次数减一并判断引用是否为零（是否调用delete），然后将新的对象引用次数加一
   6. 重载析构函数 使引用次数减一并判断是否为零（是否调用delete）

2. 线程安全问题

   1. 同一个shared_ptr被多个线程`读`是安全的

   2. 同一个shared_ptr被多个线程`写`是不安全的

      1. 证明：在多个线程中同时对一个shared_ptr循环执行两遍swap。

         shared_ptr的swap函数的作用就是和另外一个shared_ptr交换引用对象和引用计数，是写操作

         执行两遍swap之后，shared_ptr引用的对象的值应该不变

   3. 共享引用计数的不同的shared_ptr被多个线程`写`是不安全的

## unique_ptr

1. unique_ptr`“唯一”拥有其所指对象`
   1. 同一时刻只能有一个unique_ptr指向给定对象，离开作用域时，若其指向对象，则将其所指对象销毁（默认delete）
2. 定义unique_ptr时 需要将其绑定到一个new返回的指针上
3. unique_ptr不支持普通的拷贝和赋值（因为拥有指向的对象）
   1. 但是可以拷贝和赋值一个将要被销毁的unique_ptr
   2. 可以通过release或者reset将指针所有权从一个`非const的unique_ptr`转移到另一个unique_ptr

## weak_ptr

1. weak_ptr是为了配合shared_ptr而引入的一种智能指针
   1. 它的最大作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况，但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加
2. 和shared_ptr指向相同内存
   1. shared_ptr析构之后内存释放，在使用之前使用函数`lock()`检查weak_ptr是否为空指针