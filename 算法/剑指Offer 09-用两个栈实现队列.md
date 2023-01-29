# 剑指Offer 09-用两个栈实现队列

![image-20230125121253508](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230125121253508.png)

## 思路

1. 栈的特性：先进后出 
2. 队列的特性：先进先出
3. 两个栈，一个作输入栈，只管输入操作，另一个作输出栈，负责输出返回
4. 两次先进后出，负负得正即为先进先出
5. 在构造函数中完成两个栈的初始化工作，在 appendTail 函数中向其中一个栈 stack1 结尾插入整数，在 deleteHead 函数中如果 stack2 为空，则将 stack1 的值全部弹出放到 stack2 中，再从 stack2 中取值，这样达到了负负为正的队列效果


## 代码

```C++
class CQueue {
private:
    stack<int> in,out;  //输入栈和输出栈
public:
    CQueue() 
    {

    }
    
    void appendTail(int value) 
    {
        in.push(value); //压入输入栈
    }
    
    int deleteHead() 
    {
        if(!out.empty())    //输出栈不为空 直接弹出即可 注意C++ STL中的stack的pop方法返回值为void
        //应该 先top()取出再pop()弹出 以免误处理
        {
            int v_1 = out.top();    //取值
            out.pop();  //弹出
            return v_1;
        }
        else
        {
            //把所有的输入栈中的元素压入输出栈中 两次先进后出即为先进先出
            while(!in.empty())
            {
                int v_1 = in.top();
                in.pop();
                out.push(v_1);
            }
            if(out.empty())
            {
                return -1;
            }
            else
            {
                int v_2 =out.top();
                out.pop();
                return v_2;
            }
            
        }
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
```

```C++
//简化版本
class CQueue {
public:
    CQueue() {}
    
    void appendTail(int value) 
    {
        in.push(value);
    }
    
    int deleteHead() 
    {
        if(out.empty())
        {
            while(!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        if(!out.empty())
        {
            int res = out.top();
            out.pop();
            return res;
        }
        else{
            return -1;
        }
    }
private:
    stack<int> in,out;
};
```

![image-20230125121839701](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230125121839701.png)