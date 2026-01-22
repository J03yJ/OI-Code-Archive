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
const int N = 5e5 + 10;
int a[N], t = 20;
vector <int> s = {1, 2, 7};
void work1() {
	F(id, 10, 12) {
	// for (int id: s) {
		auto chk = [&] (int l, int r = - 1) -> bool {
			if (r == - 1) return id == l;
			return l <= id && id <= r;
		};
		// if (id == 13 || id == 20 || id == 11 || id == 14 || id == 17 || id == 18 || id == 19 || id == 5 || id == 8 || id == 10 || id == 15 || id == 6 || id == 3) continue;
		// if (!(chk(17, 18) || chk(3, 4) || chk(6, 7) || chk(10) || chk(12))) continue;
		// if (id == 1 || id == 2 || id == 4 || id == 5 || id == 6 || id == 7 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 19) continue;
		freopen((to_string(id) + ".in").c_str(), "w", stdout);
		int n, m, k;
		if (chk(1, 3)) {
			n = 8, m = 5;
		}
		if (chk(4, 7)) {
			n = 16, m = 10;
		}
		if (chk(8, 9)) {
			n = 100, m = 4;
		}
		if (chk(10, 12)) {
			n = 300, m = 50;
		}
		if (chk(13, 16) || chk(19, 20)) {
			n = 5000, m = 100;
		}
		if (chk(17, 18)) {
			n = 5000, m = 1;
		}
		chkmax(t, 1);
		k = rnd(0, min(100, n - 1));
		k = 4;
		int t = n / m / (k + 1);
		chkmax(t, 1);
		// t += rnd(0, 1);
		t = t * 0.2;
		chkmax(t, 1);
		debug << t << endl;
		// if (chk(17, 18)) {
		// 	t *= 100;
		// 	k = 100;
		// 	// debug << t << endl;
		// }
		cout << n << ' ' << m << ' ' << k << '\n';
		F(i, 1, n) a[i] = i;
		shuffle(a + 1, a + n + 1, mrand);
		F(i, 1, m) cout << a[i] << ' '; cout << '\n';
		if (chk(13, 14)) {
			shuffle(a + 1, a + n + 1, mrand);
			F(i, 2, n) cout << a[i - 1] << ' ' << a[i] << ' ' << rnd(1, 1e9) << '\n';
		} else if (chk(15, 16)) {
			F(i, 2, n) cout << 1 << ' ' << i << ' ' << rnd(1, 1e9) << '\n';
		} else {
			F(i, 2, n) cout << rnd(max(1, i - t), i - 1) << ' ' << i << ' ' << rnd(1, 1e9) << '\n';
		}
		// fclose(stdin);fclosbug e(stdout);
	}
}
void work2() {
	F(id, 10, 12) {
	// for (int id: s) {
		system(("\"/Users/zhaohaikun/Documents/出题/ZR2024 NOIP模拟赛10/std/barrack\" < " + to_string(id) + ".in > " + to_string(id) + ".ans").c_str());
		debug << id << " is ok.\n";
	}
}
void work3() {
	F(id, 1, t) {
	// for (int id: s) {
		debug << id << " ";
		system(("cat " + to_string(id) + ".ans").c_str());
		cout << endl;
	}
}
signed main() {
	// work1();
	// work2();
	work3();
	return 0;
}
/* why?
*/