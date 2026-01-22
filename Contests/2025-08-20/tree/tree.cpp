#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=5e5+9;

namespace ANSWER {
	const int M = 1e9 + 7, P = 20090723, N = 1e6 + 5, P2 = 998244353;
	int inv[N];
	inline void output(long long *ans, int n) {
		if(ans[1] == -1) {
			puts("-1 -1 -1 -1 -1");
			return ;
		}
		long long ans1, ans2, ans3, ans4, ans5;
		ans1 = ans2 = ans3 = ans4 = ans5 = 0ll;
		inv[0] = inv[1] = 1;
		for(int i = 1, v = P, v2 = P2; i <= n; i++, v = 1ll * v * P % M, v2 = 1ll * v2 * P2 % M) {
			if(i > 1) inv[i] = 1ll * (M - M / i) * inv[M % i] % M;
			ans1 ^= ans[i];
			ans2 ^= 1ll * ans[i] % M * i;
			ans3 += 1ll * ans[i] % M * v % M;
			ans4 += 1ll * ans[i] % M * v2 % M;
			ans5 += 1ll * ans[i] % M * inv[i] % M;
		}
		ans5 %= M;
		printf("%lld %lld %lld %lld %lld\n", ans1, ans2, ans3, ans4, ans5);
		// for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);puts("");
	}
}

ll ans[N];
int a[N],n,q;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>a[i];

		
	}

	return 0;
}