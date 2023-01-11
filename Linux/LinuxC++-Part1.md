# LinuxC++-Part1

- 实际上Linux这个词本身只表示Linux内核
- 目前Linux一般形容基于Linux内核，并且使用GNU工程各种工具和数据库的操作系统

![image-20230107144209400](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107144209400.png)

![image-20230107144245824](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107144245824.png)

![image-20230107144423524](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107144423524.png)

![image-20230107144830730](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107144830730.png)

## gcc命令的编译选项

![image-20230107145116367](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107145116367.png)

![image-20230107145130074](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107145130074.png)

## 程序的编译、链接过程

![image-20230107145208315](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107145208315.png)

## Makefile

- 可执行程序的产生过程

  - 配置环境（系统环境）--->  确定标准库和头文件的位置 ---> 确定依赖关系（源代码之间编译的依赖关系） --->头文件预编译 ---> 预处理 --->编译 --->链接  --->  安装  --->和操作系统建立联系  --->生成安装包

- Makefile

  - 当依赖关系复杂的时候，make命令工具诞生了，Makefile文件正是为make工具所使用的
  - Makefile描述了整个工程所有文件的编译顺序、编译规则

- 多个文件的简单编译示例

  - ![image-20230107150941711](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107150941711.png)

  - 普通方式

    - `g++ reply.cpp main.cpp -o main01`
    - ![image-20230107151513709](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107151513709.png)

  - Makefile方式

    - ![image-20230107152204940](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107152204940.png)

    - ```makefile
      main: reply.o main.o
      	g++ reply.o main.o -o main02
      reply.o: reply.cpp
      	g++ -c reply.cpp -o reply.o
      main.o: main.cpp
      	g++ -c main.cpp -o main.o
      ```



- make其实是一个批处理（操作系统概念）工具，本身没有什么功能
- make工具就是根据Makefile文件中的命令进行编译和链接的
- makefile工具也可以使用CMake等IDE工具编写

## Makefile的格式

- ```makefile
  目标(target)...:依赖(prerequisites)...
  	命令(command)
  ```

  注：每个命令行前面必须是一个Tab键位符

- Makefile的简化规则

  - ```
    变量定义：变量 = 字符串
    变量使用： $(变量名)
    ```

- 改写实例

  - ```C++
    main: reply.o main.o
    	g++ reply.o main.o -o main02
    reply.o: reply.cpp
    	g++ -c reply.cpp -o reply.o
    main.o: main.cpp
    	g++ -c main.cpp -o main.o
    ```

  - 新代码

  - ```makefile
    TARGET = main
    OBJS = reply.o main.o
    $(TARGET):$(OBJS)
            g++ $(OBJS) -o $(TARGET)
    reply.o: reply.cpp
    main.o: main.cpp
    
    ```

  - ![image-20230107153726949](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107153726949.png)

- 不生成目标文件的命令最好都设置为假想目标

  - ![image-20230107154255218](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107154255218.png)



- make工程的安装和卸载

  - 将程序安装到系统中

  - ```makefile
    TARGET = main
    OBJS = reply.o main.o
    
    .PHONY:clean
    
    $(TARGET):$(OBJS)
            g++ $(OBJS) -o $(TARGET)
    reply.o: reply.cpp
    main.o: main.cpp
    clean:
            rm $(TARGET) $(OBJS)
    install:
            cp ./main /usr/local/bin/mainTest
    unistall:
            rm /usr/local/bin/mainTest
    ```

  - ![image-20230107155152260](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107155152260.png)



- Makefile中的变量
  - 用户自定义变量、变量中的变量、追加变量、多行变量、环境变量、自动变量、模式变量、自动匹配
  - makefile对大小写敏感
- 变量中的变量
  - ![image-20230107160035275](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107160035275.png)可以往后放

## CMake

```cmake
cmake_minimum_required (VERSION 2.8)
project (math)
 
# 设置cmake的全局变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
 
#添加头文件路径,相当于makefile里面的-I
include_directories(${PROJECT_SOURCE_DIR}/include)
 
aux_source_directory (src SRC_LIST)
 
add_executable (main main.cpp ${SRC_LIST})
```

![image-20230107181112273](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230107181112273.png)

```cmake
cmake_minimum_required (VERSION 2.8)
project (math)
 
# 设置cmake的全局变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
 
#添加头文件路径,相当于makefile里面的-I
include_directories(${PROJECT_SOURCE_DIR}/include)
 
aux_source_directory (src SRC_LIST)
 
add_executable (main main.cpp ${SRC_LIST})
```

## VS2019配置Linux开发环境

![image-20230108102535532](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230108102535532.png)

![image-20230108102523765](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230108102523765.png)

![image-20230108102603454](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230108102603454.png)
