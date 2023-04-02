# STL容器之String字符串

## String的特性

- `char*`是一个指针，`string`是一个类
  - string封装了char*，管理这个字符串，是一个`char*`的容器
- String封装了很多实用的成员方法
  - 查找find，拷贝copy，删除delete，替换replace，插入insert
- 不用考虑内存释放和越界
  - string管理char*所分配的内存，每一次string的赋值，取值都由string类维护，不用担心复制越界和取值越界问题

> string和char*可以互相转换吗？
>
> 可以转换，string转char*通过string提供的c_str()方法
>
> char*转换为string，通过sstr(s)方法

```C++
//string 转 char*
string str = "itcast";
const char* cstr = str.c_str();
//char* 转 string 
char* s = "itcast";
string sstr(s);
```

## String常用API

### 构造函数

```C++
string();//创建一个空的字符串 例如: string str;      
string(const string& str);//使用一个string对象初始化另一个string对象
string(const char* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化 
//例子:
//默认构造函数
string s1;
//拷贝构造函数
string s2(s1);
string s2 = s1;
//带参数构造函数
char* str = "itcast";
string s3(str);
string s4(10, 'a');
```

### 基本赋值操作

```C++
string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string& operator=(const string &s);//把字符串s赋给当前的字符串
string& operator=(char c);//字符赋值给当前的字符串
string& assign(const char *s);//把字符串s赋给当前的字符串
string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
```

### 存取字符操作

```C++
char& operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符
//例子:
string s = "itcast";
char c = s[1];
c = s.at(1);
```

> []和at的异同？
>
> 相同点：[]和at都可以返回第n个字符
>
> 不同点，at访问越界会抛出异常，[]越界会直接程序会挂掉

### 拼接操作

```C++
string& operator+=(const string& str);//重载+=操作符
string& operator+=(const char* str);//重载+=操作符
string& operator+=(const char c);//重载+=操作符
string& append(const char *s);//把字符串s连接到当前字符串结尾
string& append(const char *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
string& append(const string &s);//同operator+=()
string& append(const string &s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c);//在当前字符串结尾添加n个字符c
```

### 查找和替换

```C++
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
```

### 比较操作

```C++
/*
compare函数在>时返回 1，<时返回 -1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。
*/
int compare(const string &s) const;//与字符串s比较
int compare(const char *s) const;//与字符串s比较
```

### 插入和删除操作

```C++
string& insert(int pos, const char* s); //插入字符串
string& insert(int pos, const string& str); //插入字符串
string& insert(int pos, int n, char c);//在指定位置插入n个字符c
string& erase(int pos, int n = npos);//删除从Pos开始的n个字符 
```

### Test

```C++
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "abc";
    cout << s.find('a') << endl;
    cout << s + 'd' << endl;
    cout << s.at(1) << endl;
    cout << s[2] << endl;
}
```

![image-20230331101623335](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230331101623335.png)