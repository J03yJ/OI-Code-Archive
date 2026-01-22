#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int T, _[66], * P = _ + 1, n, l, ans; long long m;
int R(int x, int y) { return (x += y) >= MOD ? x - MOD : x; }
int qpow(int x, int y) { int t = 1; for (; y; y>>=1) y & 1 ? t = 1ll * t * x % MOD : 0, x = 1ll * x * x % MOD; return t; }
int main() {
	freopen ("xor.in", "r", stdin);
	freopen ("xor.out", "w", stdout);
	cin >> T;
	P[-1] = MOD + 1 >> 1, P[0] = 1;
	for (int i=1; i<=60; i++) P[i] = R(P[i-1], P[i-1]);
	while (T --) {
		scanf ("%lld", &m), n = m % (MOD - 1), scanf ("%lld", &m), l = 0;
		while (1ll << l < m) l ++; m --, ans = R(P[l], n & 1 ? MOD - m % MOD : 0);
		for (int i=0; i<l; i++) if (m >> i & 1) {
			int v = ((m & (1ll << i) - 1) + 1) % MOD, h = n & 1 ? (m >> i << i) % MOD : P[i], t = R(P[l], R(MOD - h, P[-1]));
			ans = (ans + 1ll * t * qpow(R(v, P[i]), n) + 1ll * P[i-1] * qpow(R(MOD - v, P[i]), n) + 1ll * R(t, n & 1 ? MOD - P[i-1] : P[i-1]) * (MOD - qpow(v, n))) % MOD;
		} printf ("%d\n", ans);
	}
}
