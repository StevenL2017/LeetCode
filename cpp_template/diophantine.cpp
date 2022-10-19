#include <cmath>

using namespace std;

// solve ax + by = m
long long gcd(long long a, long long b, long long& x, long long& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long x1, y1;
	long long d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}

bool find_any_solution(long long a, long long b, long long m, long long& x, long long& y, long long& g) {
	g = gcd(abs(a), abs(b), x, y);
	if (m % g) {
		return false;
	}
	x *= m / g;
	y *= m / g;
	if (a < 0) x = -x;
	if (b < 0) y = -y;
	return true;
}