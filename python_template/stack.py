# 枚举极小值的贡献，探索每个元素作为极值时两侧的边界
# 左边界严格大于当前元素，右边界大于等于当前元素
def min_range(nums):
    n = len(nums)
    stack = []
    left, right = [-1] * n, [n] * n
    for i in range(n):
        while stack and nums[i] <= nums[stack[-1]]:
            right[stack.pop()] = i
        if stack:
            left[i] = stack[-1]
        stack.append(i)
    return left, right

# 枚举极大值的贡献，探索每个元素作为极值时两侧的边界
# 左边界严格小于当前元素，右边界小于等于当前元素
def max_range(nums):
    n = len(nums)
    stack = []
    left, right = [-1] * n, [n] * n
    for i in range(n):
        while stack and nums[i] >= nums[stack[-1]]:
            right[stack.pop()] = i
        if stack:
            left[i] = stack[-1]
        stack.append(i)
    return left, right