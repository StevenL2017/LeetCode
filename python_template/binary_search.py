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