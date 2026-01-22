// MagicDark
#include <bits/stdc++.h>
#define debug cerr << "\33[32m[" << __LINE__ << "]\33[m "
#define SZ(x) ((int) x.size() - 1)
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> T& chkmax(T& x, T y) {return x = max(x, y);}
template <typename T> T& chkmin(T& x, T y) {return x = min(x, y);}
template <typename T> T& read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = - f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x *= f;
}
mt19937 mrand(chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l, int r) {return mrand() % (r - l + 1) + l;}
const int N = 2e6 + 10;
int a[N];
void work1() {
	int t = 5;
	cout << t << '\n';
	F(_, 1, t) {
		int n = _ * 100;
		cout << n << '\n';
		F(i, 1, n) cout << rnd(1, 2) << ' '; cout << '\n';
	}
}
signed main() {
	work1();
	return 0;
}
/* why?
*/