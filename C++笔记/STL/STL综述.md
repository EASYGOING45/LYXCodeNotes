# STL综述

## STL基本概念

STL(Standard Template Library,标准模板库)，是惠普实验室开发的一系列软件的统称。现在主要出现在c++中，但是在引入c++之前该技术已经存在很长时间了。

STL从广义上分为: `容器(container) 算法(algorithm) 迭代器(iterator),`容器和算法之间通过迭代器进行无缝连接。STL几乎所有的代码都采用了模板类或者模板函数，这相比传统的由函数和类组成的库来说提供了更好的代码重用机会。

STL(Standard Template Library)标准模板库,在我们c++标准程序库中隶属于STL的占到了80%以上。

在C++标准中，STL被组织成了13个头文件：

`<algorithm>、<deque>、<functional>、<iterator>、<vector>、<list>、<map>、<memory>、<numeric>、<queue>、<set>、<stack> 和<utility>`

STL还有以下优点：

- STL是C++的一部分，因此不用额外安装什么，它被内建在编译器中
- STL的一个重要特点是数据结构和算法的分离。尽管这是个简单的概念，但是这种分离确实使得STL变得非常通用。
  - 例如：在STL的vector容器中，可以放入元素、基础数据类型变量、元素的地址：STL的sort()排序函数可以用来操作vector、list等容器
- 程序员可以不用思考STL具体的实现过程

STL具有高可重用性，高性能，高移植性，跨平台的优点。

- 高可重用性：STL中几乎所有的代码都采用了模板类和模版函数的方式实现，这相比于传统的由函数和类组成的库来说提供了更好的代码重用机会。关于模板的知识，已经给大家介绍了。
- 高性能：如map可以高效地从十万条记录里面查找出指定的记录，因为map是采用红黑树的变体实现的。(红黑树是平横二叉树的一种)
- 高移植性：如在项目A上用STL编写的模块，可以直接移植到项目B上。
- 跨平台：如用windows的Visual Studio编写的代码可以在Mac OS的XCode上直接编译。

## STL三大组件介绍

### 容器

STL中容器是指存储有限数据元素的一种数据结构。比如栈（stack）、队列（queue）...

把数据按照特定的方式排列起来，便于我们查找、删除、排序或者其他一些目的，这种不同的排列方式我们称之为数据结构。

![image-20230402093114585](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230402093114585.png)

教室中包含了很多学生，教室就是一个容器，学生就是容器中存储的一个元素，教学楼包含了很多教室，教学楼就是一个容器，教室就是容器中的一个元素。

这里面还包含了一层含义：`容器可以包含容器`(教学楼和教室都是容器，但是教学楼里可以放教室)

比如拿教室这个容器来举例：我们怎么能快速定位教室中某个人的位置，是不是需要我们教室中的所有人按照一定的规则排序，这样我就能快速定位一个学生的坐在那里，那么依据我们的需求，让学生按照不同的规则排列，这种不同的排列就叫做数据结构。

STL中容器分为 `序列式容器`和 `关联式容器`

1. 序列式容器就是根据学生进入教室的时间和地点来决定学生在那个位置，跟学生是谁没关系。
2. 关联式容器是指我教室的座位按照一定规则确定好了，每个学生进来，比如根据学生出生年月，从小到大排列，学生坐在那个位置，必须由我的规则来规定。

### 迭代器

迭代器是一种抽象出来的概念，现实中不容易找出来某项事物与之对应，所以较难理解。

但是在我们程序中，比如我们写的数据，我们通过[]操作符遍历取值，那么`[]`就是一个迭代器，也必须说我们经常用的指针，他也是一种迭代器。

迭代器（iterator）是一种对象，它能够用来遍历标准模板库容器中的部分或全部元素，每个迭代器对象代表容器中的确定的地址。迭代器修改了常规指针的接口，所谓迭代器是一种概念上的抽象：那些行为上像迭代器的东西都可以叫做迭代器，也就是说迭代器就是对我们普通的指针做了一层封装，其行为也类似指针。我们现在呢？可以单纯得把迭代器理解为，它就是一个指针，用来指向不同的元素,既然是指针，那么指针的一些基本运算操作，比如*、++、==、!=、=,迭代器也可以进行这样的操作。

### 算法

以有限的步骤，解决逻辑或者数学上的问题，这门学科我们就叫做算法。一般来说，我们每天都在写各种各样的算法，比如我们写的每一个函数，它被用来解决或大或小的问题。

在我们工作中，我们要写一个算法来解决一个问题的时候，那么需要考虑你写的算法需要消耗的计算机资源，包括时间和空间，如果你写一个算法需要消耗1G内存来解决这个问题，那么你这个算法也就没有什么价值了。

  STL为我们的提供的算法，都很高效，而且还有个最大的特点，可复用性。那么我们学习算法，就很简单了，我们只需要去熟悉并且能熟练应用STL为我们提供的常用算法就OK了。

STL提供了大约100个实现算法的模版函数，比如算法for_each将为指定序列中的每一个元素调用指定的函数等。这样一来，只要我们熟悉了STL之后，许多代码可以被大大的化简，只需要通过调用一两个算法函数，就可以完成所需要的功能并大大地提升效率