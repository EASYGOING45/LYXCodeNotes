# 剑指Offer 03-数组中重复的数字

![image-20230128104835558](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230128104835558.png)

## 思路

### 哈希

- 初始化： 新建 HashSet ，记为 dicdicdic ；
- 遍历数组 nums 中的每个数字 num ：
  - 当 num 在 dic 中，说明重复，直接返回 num ；
  - 将num添加到dic中
- 返回 -1

### 交换索引

![image-20230128105353371](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230128105353371.png)

遍历中，第一次遇到数字 x时，将其交换至索引 x 处；而当第二次遇到数字x 时，一定有 nums[x]=x ，此时即可得到一组重复数字。

## 代码

```C++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
       //哈希表 unordered_map
        unordered_map<int,bool> map;
        for(int num:nums)
        {
            if(map[num]) return num;    //如果存在 则直接返回
            map[num] = true;
        }
        return -1;
    }
};
```

```C++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            if(nums[i] == i) {
                i++;
                continue;
            }
            if(nums[nums[i]] == nums[i])
                return nums[i];
            swap(nums[i],nums[nums[i]]);
        }
        return -1;
    }
};

```

