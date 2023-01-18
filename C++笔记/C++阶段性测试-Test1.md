# C++阶段性测试-Test1

## 1、以下为WindowsNT 32位C++程序，请计算下面sizeof的值

```C++
char str[] = "hello";
char* p = str;
int n = 10;
// 请计算
sizeof(str) = ?
sizeof(p) = ?
sizeof(n) = ?
    
void Func(char str[100])
 {
 	// 请计算
	 sizeof(str) = ?
 }

void* p = malloc(100);
// 请计算
sizeof(p) = ？
```

1. sizeof(str)=6 sizeof计算的是数组的所占内存的大小，包含其末尾的'\0'

2. sizeof(p)=4 p为指针变量，32位系统下大小位4bytes

3. sizeof(n)=4 n是整形变量，占用内存空间为4字节

4. void Func里面 sizeof(str)=4 函数的参数为字符数组名 即数组首元素地址 大小为指针的大小

5. ```C++
   void* p=malloc(100)
   sizeof(p)=4
   ```

   p指向malloc分配的大小为100byte的内存的起始地址，sizeof(p)为指针的大小，而不是它指向内存的大小

## 2、分析运行下面的各个Test函数会有什么样的结果

1. ```C++
   void GetMemory1(char* p)
   {
    	p = (char*)malloc(100);
   }
   void Test1(void)
   {
    	char* str = NULL;
    	GetMemory1(str);
    	strcpy(str, "hello world");
    	printf(str);
   }
   ```

   程序崩溃。因为Get1函数并不能传递动态内存，其返回值为void，Test1中的str时钟为Null，strcpy是程序崩溃

2. ```C++
   char *GetMemory2(void)
   {
   	 char p[] = "hello world";
    	return p;
   }
   void Test2(void)
   {
    	char *str = NULL;
    	str = GetMemory2();
    	printf(str);
   }
   ```

   可能是乱码。因为Get2函数返回的是指向栈区内存的指针，该指针的地址不是NULL，使其原先的内容已经配清楚，新内容不可知，栈区内存在函数外不在作用域内会自动销毁

3. ```C++
   void GetMemory3(char** p, int num)
   {
    	*p = (char*)malloc(num);
   }
   void Test3(void)
   {
   	 char* str = NULL;
    	GetMemory3(&str, 100);
    	strcpy(str, "hello");
    	printf(str);
   }
   ```

   能够输出hello，但会导致内存泄漏，因为Get3函数申请的内存没有释放

4. ```C++
   void Test4(void)
   {
       char *str = (char*)malloc(100);
   	 strcpy(str, "hello");
        free(str);
   	 if(str != NULL) 
        {
    		strcpy(str, "world");
   		 cout << str << endl;
    	 }
   }
   ```

   篡改了动态内存区的内容，后果难以预计，非常危险，因为free(str)之后，str成为了野指针，if(str!=NULL)语句不起作用

## 3、实现内存拷贝函数

```C++
char* strcpy(char* strDest,const char* strSrc);
```

解：

```C++
char* strcpy(char*dst,const char *src)		//[1]
{
	assert(dst != NULL && src != NULL);		//[2]
	char *ret = dst;	//[3]
	while((*dst++=*src++)!='\0');	//[4]
	return ret;
}
```

1. const修饰:源字符串参数用const修饰，防止修改源字符串
2. 空指针检查：
   1. 检查指针的有效性，有助于增强代码的健壮性
   2. 检查指针的有效性时，使用 `assert(!dst && !src);`
      1. char*转换为bool是类型隐式转换，这种功能虽然灵活，但更多的是导致出错概率增大和维护成本升高
   3. 检查指针的有效性时使用 `assert(dst !=0 && src !=0);`
      1. 直接使用常量（如0），会减少程序的可维护性，而是用NULL代替0，如果出现拼写错误，编译器会查出来
3. 返回目标地址
   1. 忘记保存原始的strdst值
4. '\0'
   1. 循环写成 `while((*dst++=*src++)!='\0');`是错误的
   2. 应该写成  `while(*src!='\0') *dst++ = *src++;`
      1. 循环体结束后，dst字符串的末尾没有正确地加上'\0'
   3. 为何要返回char*
      1. 返回dst的原始值使函数能够支持链式表达

