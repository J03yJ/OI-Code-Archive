#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using uint=unsigned;
using ull=unsigned long long;
const int N=3e5+9;
const int D=1e1+9;
const int T=(1<<12)+9;

int a[N],n,d,p,q,lim;
int A[N],B[N],C[N],l1[N],r1[N],l2[N],r2[N];
uint w[N],z[T];

namespace P2{
	uint ans[N];
	#define popc __builtin_popcount
	
	inline void Solve(){
		for(int i=1;i<=q;i++){
			for(int j=l1[i];j<=r1[i];j++){
				vector<ll> tmp;
				for(int k=1;k<=n;k++){
					tmp.push_back(ll(A[i])*popc(a[k]&j)+ll(B[i])*popc(a[k]|j)+ll(C[i])*popc(a[k]^j));
				}
				tmp.push_back(0);
				sort(tmp.begin(),tmp.end());
				for(int k=l2[i];k<=r2[i];k++){
					ans[i]+=uint(tmp[k])*z[j]*w[k];
				}
			}
			cout<<ans[i]<<endl;
		}
	}
	#undef popc
}
namespace P3{
	inline void Solve(){

	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>d>>p;
	lim=round(powl(p,d));
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=0;i<lim;i++) cin>>z[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>A[i]>>B[i]>>C[i]>>l1[i]>>r1[i]>>l2[i]>>r2[i];

	if(p==2) P2::Solve();
	else P3::Solve();

	return 0;
}