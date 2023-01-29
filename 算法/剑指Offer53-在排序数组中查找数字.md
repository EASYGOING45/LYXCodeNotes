# 剑指Offer53-在排序数组中查找数字

![image-20230129091742606](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230129091742606.png)

## 思路

- 暴力，没啥好说的
- 二分
  - 由于数组已经排序，因此整个数组是**单调递增**的，我们可以利用二分法来加速查找的过程。
  - 考虑 target在数组中出现的次数，其实我们要找的就是数组中「第一个等于 target的位置」（记为 leftIdx）和「第一个大于 target的位置减一」（记为 rightIdx）。当 target在数组中存在时，target 在数组中出现的次数为 rightIdx−leftIdx+1。


## 代码

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) 
    {
        int count = 0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]==target)
            {
                count++;
            }
        }
        return count;
    }
};
```

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) 
    {
        //二分查找
        if(nums.empty())
        {
            return 0;
        }
        int l=0,r=nums.size()-1;    //左右索引 开始位置
        while(l<r)
        {
            int mid = (l+r) / 2;
            if(nums[mid]>= target) r=mid;
            else l = mid+1;
        }
        if(nums[r]!=target) return 0; //查找失败
        int begin = r;
        l=0,r=nums.size()-1;
        while(l<r)
        {
            int mid=(l+r+1)/2;
            if(nums[mid]<=target) l=mid;
            else r=mid-1;
        }
        int end=r;
        return end-begin+1;
    }
};
```

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        //先 二分查找 找到元素
        int left = 0;int right = n-1;
        while( left <= right ){
            int mid = (right-left)/2+left;
            if( nums[mid] > target )    right = mid-1;
            else if( nums[mid] < target )  left = mid+1;
            else{
                left = mid;
                right = mid;
                break;
            }
        }
        while( left>=1 && nums[left-1] == target )    left--;
        while( right<n-1 && nums[right+1] == target )  right++;
        return right-left+1;
    }
};


```

