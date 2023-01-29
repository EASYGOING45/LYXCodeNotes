# 剑指Offer 05-替换空格

![image-20230127102346982](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230127102346982.png)

### 常规

```C++
class Solution {
public:
    string replaceSpace(string s) {
        string ans;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==' ')
            {
                ans+="%20";
            }
            else
            {
                ans += s[i];
            }
        }
        return ans;
    }
};
```



### 不借助额外空间做法（双指针)

```C++
class Solution {
public:
    string replaceSpace(string s) 
    {
        //极致做法
        int count = 0;  //统计空格
        int oldSize = s.size();
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==' ')
            {
                count++;
            }
        }
        //扩充字符串s的大小 替换 % 20
        s.resize(s.size()+count*2);
        int newSize = s.size();

        //从后往前替换空格为%20
        for(int i=newSize-1,j=oldSize-1;j<i;i--,j--)
        {
            if(s[j]!=' ')
            {
                s[i] = s[j];
            }
            else
            {
                s[i]='0';
                s[i-1]='2';
                s[i-2]='%';
                i-=2;
            }
        }
        return s;
    }
};
```

