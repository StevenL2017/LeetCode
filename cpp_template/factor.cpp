#include <vector>
#include <algorithm>

using namespace std;

vector<int> factor(int num) {
    vector<int> ans;
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            ans.push_back(i);
            if (num / i != i) {
                ans.push_back(num / i);
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

vector<int> prime_factor(int num) {
    vector<int> ans;
    for (int i = 2; i * i <= num; i++) {
        while (num % i == 0) {
            ans.push_back(i);
            num /= i;
        }
    }
    if (num > 1) ans.push_back(num);
    sort(ans.begin(), ans.end());
    return ans;
}