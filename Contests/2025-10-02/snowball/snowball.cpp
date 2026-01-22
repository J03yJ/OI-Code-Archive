#include<bits/stdc++.h>

using namespace std;

ifstream fin("snowball.in");
ofstream fout("snowball.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const ll mod=2500000001;

inline void AddAs(ll &x,ll y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(ll &x,ll y){if((x-=y)<0) x+=mod;}
inline void MulAs(ll &x,ll y){x=1ll*x*y%mod;}
inline ll Add(ll x,ll y){if((x+=y)>=mod) x-=mod;return x;}
inline ll Sub(ll x,ll y){if((x-=y)<0) x+=mod;return x;}
inline ll Mul(ll x,ll y){return 1ll*x*y%mod;}
inline ll QPow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

const int K=1e3+9;
const int N=5e4+9;

ll d[N<<2];
int a[K],b[K],p[K],n,m,k;
inline void Add(int l,int r,int k){d[l]+=k,d[r+1]-=k;}
inline void Calc(){for(int i=1;i<=n+m+1;i++) d[i]+=d[i-1];}
inline void Clear(){for(int i=0;i<=n+m+1;i++) d[i]=0;}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=k;i++) cin>>a[i]>>b[i];

		iota(p+1,p+k+1,1);
		sort(p+1,p+k+1,[](int i,int j){return b[i]<b[j];});
		for(int i=1;i<=n;i++){
			vector<int> stk,t;
			for(int j=1;j<=k;j++){
				int x=p[j],l=abs(a[x]-i);
				if(stk.size()&&l>=t.back()+b[x]-b[stk.back()]) continue ;
				while(stk.size()&&t.back()>=l+b[x]-b[stk.back()]){
					stk.pop_back();
					t.pop_back();
				}
				stk.push_back(x);
				t.push_back(l);
			}
			for(int x:t) Add(x,x,1);
			Add(t.front()+1,t.front()+b[stk.front()]-1,1);
			Add(t.back()+1,t.back()+m-b[stk.back()],1);
			for(int j=0;j+1<stk.size();j++){
				int r1=t[j]+t[j+1]+(b[stk[j+1]]-b[stk[j]]-1)>>1;
				int r2=t[j]+t[j+1]+(b[stk[j+1]]-b[stk[j]]-1)+1>>1;
				Add(t[j]+1,r1,1);
				Add(t[j+1]+1,r2,1);
			}
		}
		Calc();
		Calc();

		ll ans=1,inv=1;
		for(int i=0;i<min(1ll*n*m,ll(n+m));i++) MulAs(ans,d[i]-i),MulAs(inv,1ll*n*m-i);
		MulAs(ans,Inv(inv));

		cout<<ans<<endl;

		Clear();
	}

	return 0;
}