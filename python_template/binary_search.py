from typing import *

# 左闭右闭
def binary_search_1():
    def check():
        pass

    left, right = 1, 10 ** 9
    ans = left
    while left <= right:
        mid = left + (right - left) // 2
        if check(mid):
            left = mid + 1
            ans = mid
        else:
            right = mid - 1
    return ans

# 左闭右开
def binary_search_2():
    def check():
        pass

    left, right = 1, 10 ** 9
    while left < right:
        mid = left + (right - left) // 2
        if check(mid):
            left = mid + 1
        else:
            right = mid
    return left

# 三分法求严格凸函数 fn 在 [lower, upper] 闭区间内的最小值
def minimize(fn: Callable, lower: int, upper: int) -> int:
    ans = float('inf')
    while upper - lower >= 3:
        diff = upper - lower
        mid1 = lower + diff // 3
        mid2 = lower + 2 * diff // 3
        if fn(mid1) > fn(mid2):
            lower = mid1
        else:
            upper = mid2
    while lower <= upper:
        ans = min(ans, fn(lower))
        lower += 1
    return ans