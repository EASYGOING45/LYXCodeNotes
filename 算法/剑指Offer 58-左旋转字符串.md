# 剑指Offer 58-左旋转字符串

![image-20230127104152185](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230127104152185.png)

### 纯暴力

```C++
class Solution {
public:
    string reverseLeftWords(string s, int n) 
    {
        string s1;
        string s2;
        if(n==0)
        {
            return s;
        }
        for(int i=0;i<n;i++)
        {
            s1+=s[i];
        }
        s2=s.substr(n,s.size());
        s2+=s1;
        
        return s2;
    }
};
```

```C++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        if(s.size()==0) return s;
        string s1 = s.substr(0,n);
        string res = s.substr(n,s.size()-n) + s1;
        return res;
    }
};
```

### 花式翻转

![image-20230127104201428](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230127104201428.png)

```C++
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        //花式翻转
        reverse(s.begin(),s.begin()+n); //翻转前n
        reverse(s.begin()+n,s.end());   //翻转区间n到末尾
        reverse(s.begin(),s.end()); //翻转整个
        return s;
    }
};
```

