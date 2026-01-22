// LUOGU_RID: 158054210
#include <bits/stdc++.h>
using namespace std;
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define ld long double
#define FOR(i,n,m) for(int i=(n);i<=(m);i++)
#define ROF(i,n,m) for(int i=(n);i>=(m);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define SZ(v) v.size()
#define PII pair<int, int>
#define FI(v) v.first
#define SE(v) v.second
#define endl '\n'
template < typename A, typename B >
inline bool chmax(A &x, B y) { return (x < y ? (x = y, true) : false); }
template < typename A, typename B >
inline bool chmin(A &x, B y) { return (x > y ? (x = y, true) : false); }
template <uint p>
struct Modint {
	uint x;
	Modint() {
		x = 0;
	}
	Modint(uint _x) {
		x = _x % p;
	}
	friend istream& operator >> (istream &is, Modint &A) {
		return is >> A.x;
	}
	friend ostream& operator << (ostream &os, Modint A) {
		return os << A.x;
	}
	uint add(uint x, uint y) {
		return (x + y < p ? x + y : x + y - p); 
	}
	void Add(uint &x, uint y) {
		x = (x + y < p ? x + y : x + y - p); 
	}
	uint sub(uint x, uint y) {
		return (x < y ? x - y + p : x - y);
	}
	void Sub(uint &x, uint y) {
		x = (x < y ? x - y + p : x - y);
	}
	uint mul(uint x, uint y) {
		return (1ull * x * y) % p;
	}
	void Mul(uint &x, uint y) {
		x = (1ull * x * y) % p;
	}
	uint fp(uint x, uint y) {
		uint res = 1;
		for(; y; y >>= 1) {
			if(y & 1) Mul(res, x);
			Mul(x, x);
		}
		return res;
	}
	Modint inv() {
		return Modint(fp(x, p - 2));
	}
	bool operator < (const Modint &A) const {
		return x < A.x;
	}
	bool operator > (const Modint &A) const {
		return x > A.x;
	}
	bool operator == (const Modint &A) const {
		return x == A.x;
	}
	bool operator != (const Modint &A) const {
		return x != A.x;
	}
	bool operator < (const uint &A) const {
		return x < A;
	}
	bool operator > (const uint &A) const {
		return x > A;
	}
	bool operator == (const uint &A) const {
		return x == A;
	}
	bool operator != (const uint &A) const {
		return x != A;
	}
	Modint operator + (const Modint &A) {
		return Modint(add(x, A.x));
	}
	Modint operator - (const Modint &A) {
		return Modint(sub(x, A.x));
	}
	Modint operator * (const Modint &A) {
		return Modint(mul(x, A.x));
	}
	Modint operator / (const Modint &A) {
		return Modint(mul(x, fp(A.x, p - 2)));
	}
	Modint operator + (const uint &A) {
		return Modint(add(x, A));
	}
	Modint operator - (const uint &A) {
		return Modint(sub(x, A));
	}
	Modint operator * (const uint &A) {
		return Modint(mul(x, A));
	}
	Modint operator / (const uint &A) {
		return Modint(mul(x, fp(A, p - 2)));
	}
	Modint& operator += (const Modint &A) {
		return *this = *this + A;
	}
	Modint& operator -= (const Modint &A) {
		return *this = *this - A;
	}
	Modint& operator *= (const Modint &A) {
		return *this = *this * A;
	}
	Modint& operator /= (const Modint &A) {
		return *this = *this / A;
	}
	Modint& operator += (const uint &A) {
		return *this = *this + A;
	}
	Modint& operator -= (const uint &A) {
		return *this = *this - A;
	}
	Modint& operator *= (const uint &A) {
		return *this = *this * A;
	}
	Modint& operator /= (const uint &A) {
		return *this = *this / A;
	}
};
const int P = 998244353;
typedef Modint<P> mint;
const int N = 2.5e4 + 4;
const int SN = 2.5e2 + 5;
int n, sn;
string s;
int tr[N * SN][26], idx;
vector<PII> e[N * SN]; 
int f[N * SN], ans;
struct fenwick {
	int c[N];
	int lowbit(int x) {
		return -x & x;
	}
	void modify(int u, int x) { u++;
		for(int i = u; i <= n + 1; i += lowbit(i)) {
			chmax(c[i], x);
		}
	}
	int query(int u) { u++;
		int res = 0;
		for(int i = u; i; i -= lowbit(i)) {
			chmax(res, c[i]);
		}
		return res;
	}
} t;
void dfs(int u) {
	REP(i, SZ(e[u])) {
		auto h = e[u][i];
		f[i] = t.query(FI(h) - 1) + 1;
		chmax(ans, f[i]);
	}
	REP(i, SZ(e[u])) {
		auto h = e[u][i];
		t.modify(SE(h), f[i]);
	}
	REP(i, 26) if(tr[u][i]) {
		dfs(tr[u][i]);
	}
}
void solve() {
	cin >> n;
	cin >> s; s = ' ' + s;
	sn = sqrt(n << 1) + 2;
	FOR(l, 1, n) {
		int u = 0;
		FOR(r, l, n) {
			if(r - l + 1 > sn) break;
			if(!tr[u][s[r] - 'a']) tr[u][s[r] - 'a'] = ++idx;
			u = tr[u][s[r] - 'a'];
			e[u].emplace_back(l, r);
		}
	}
	dfs(0);
	cout << ans << endl;
}
int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
	return 0;
}
