# 剑指Offer 53-0～n-1中缺失的数字

![image-20230129092037738](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230129092037738.png)

```C++
class Solution {
public:
    int missingNumber(vector<int>& nums) 
    {
        int l=0,r=nums.size()-1;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(nums[mid]>mid) r=mid-1;
            else l=mid+1;
        }
        return l;
    }
};
```

```C++
class Solution {
public:
    int missingNumber(vector<int>& nums) 
    {
        int res=-1;
        int left=0,right=nums.size()-1;
        while(left<=right)
        {
            int mid = left+(right-left)/2;
            if(mid == nums[mid]) left=mid+1;
            else
            {
                res = mid;
                right = mid-1;
            }
        }
        return res == -1 ? nums.size() : res;
    }
};
```

