#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 I;
typedef pair <I, int> pIi;
const int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
const int l = 1.6e7;
const I N = I (1e18) * I (1e18);
int pc, p[l/10], cnt; bitset <l+10> isnp; I p5[l/10];
int T, q, ans[10005]; I n; pIi x[10005];
I read() {
	I s = 0; char ch = getchar();
	while (! isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s;
}
void write(I x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
I qmul(I x, I y, I p) {
	I t = 0;
	for (; y; y>>=1) {
		if (y & 1) if ((t += x) >= p) t -= p;
		if ((x <<= 1) >= p) x -= p;
	} return t;
}
I qpow(I x, I y, I p) {
	I t = 1;
	for (; y; y>>=1) {
		if (y & 1) t = qmul(t, x, p);
		x = qmul(x, x, p);
	} return t;
}
bool MillerRabin(I p) {
	if (p == 1) return 0;
	I u = p - 1, x, y; int t = 0;
	while (! (u & 1)) u >>= 1, t ++;
	for (int i=0; i<11; i++)
		if (p == base[i]) return 1;
	for (int i=0; i<11; i++) {
		x = qpow(base[i], u, p);
		for (int j=1; j<=t; j++, x=y) {
			y = qmul(x, x, p);
			if (y == 1 && x != 1 && x != p - 1)
				return 0;
		}
		if (x != 1) return 0;
	} return 1;
}
int calc(I n) {
	{
		int l = 2, r = 1e9; if (n < r) r = n;
		while (l <= r) {
			int x = l + r >> 1; I p = (I) x * x * x * (x - 1);
			if (p == n) return x > 2 && MillerRabin(x);
			else p < n ? l = x + 1 : r = x - 1;
		}
	}
	{
		ll l = 2, r = 1e12; if (n < r) r = n;
		while (l <= r) {
			ll x = l + r >> 1; I p = (I) x * x * (x - 1);
			if (p == n) return x > 2 && MillerRabin(x);
			else p < n ? l = x + 1 : r = x - 1;
		}
	}
	{
		ll l = 2, r = 1e18; if (n < r) r = n;
		while (l <= r) {
			ll x = l + r >> 1; I p = (I) x * (x - 1);
			if (p == n) return x > 2 && MillerRabin(x);
			else p < n ? l = x + 1 : r = x - 1;
		}
	}
	return 0;
}
int main() {
	freopen ("npc.in", "r", stdin);
	freopen ("npc.out", "w", stdout);
	for (int i=2; i<=l; i++) {
		if (! isnp[i]) p[++pc] = i;
		for (int j=1; j<=pc && i*p[j]<=l; j++) {
			isnp[i*p[j]] = 1;
			if (! (i % p[j])) break;
		}
	}
	for (int i=2; i<=pc; i++) {
		I phi = p[i] - 1; double l = log10(p[i]), lj = log10(p[i] - 1);
		for (int j=1; lj<37 && phi<=N; j++, lj+=l, phi*=p[i])
			if (j >= 5) p5[++cnt] = phi;
	}
	sort (p5+1, p5+cnt+1);
	T = read();
	for (int i=1; i<=T; i++) {
		n = read();
		if (n == 1) ans[i] = 1;
		else if (n == 2) ans[i] = 3;
		else if (n & 1) ans[i] = 0;
		else ans[i] = MillerRabin(n + 1) << 1, x[++q] = pIi (n, i);
	}
	sort (x+1, x+q+1);
	for (int i=1, j=1; i<=q; i++) {
		n = x[i]. first; int id = x[i]. second;
		while (j <= cnt && p5[j] < n) j ++;
		ans[id] += p5[j] == n ? 2 : calc(n) << 1;
	}
	for (int i=1; i<=T; i++)
		printf ("%d\n", ans[i]);
}
