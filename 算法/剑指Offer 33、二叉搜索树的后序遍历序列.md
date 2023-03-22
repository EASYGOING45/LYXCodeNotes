# 剑指Offer 33、二叉搜索树的后序遍历序列

![image-20230321152008662](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230321152008662.png)

```C++
class Solution {
public:
    bool subProcess(vector<int>& nums,int start,int end)
    {
        if(start>=end) return true;
        int index=start;
        while(nums[index]<nums[end])
            index++;
        int mid = index;
        while(nums[index]>nums[end])
            index++;
        bool left=subProcess(nums,start,mid-1);
        bool right=subProcess(nums,mid,end-1);
        return left && right &&(index==end);
    }
    bool verifyPostorder(vector<int>& postorder) 
    {
        //递归
        return subProcess(postorder,0, postorder.size() - 1);
    }
};
```

