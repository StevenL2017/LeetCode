from bisect import *

# 最长递增子序列：贪心 + 二分优化
def LIS(nums):
    d, ans = [], []
    for num in nums:
        # 递增为>=, 严格递增为>
        if not d or num >= d[-1]:
            d.append(num)
            ans.append(len(d))
        else:
            # 递增为bisect_right, 严格递增为bisect_left
            idx = bisect_right(d, num)
            ans.append(idx + 1)
            d[idx] = num
    return len(d)