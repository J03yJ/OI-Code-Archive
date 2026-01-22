#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e6+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
#define Inv(x) QPow(x,mod-2)

int x[N],y[N],cnt[N],r[N],o[N],n,k;

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=k;i++) cin>>x[i]>>y[i],x[i]--;

	vector<int> yval(y+1,y+k+1);
	yval.push_back(-1);
	sort(yval.begin(),yval.end());
	yval.erase(unique(yval.begin(),yval.end()),yval.end());
	for(int i=1;i<=k;i++) y[i]=lower_bound(yval.begin(),yval.end(),y[i])-yval.begin();

	for(int i=1;i<=k;i++) cnt[y[i]]++;

	int l[2]={k+1,k+1},r[2]={0,0};
	for(int i=1;i<=k;i++){
		o[y[i]]|=x[i];
		l[x[i]]=min(l[x[i]],y[i]);
		r[x[i]]=max(r[x[i]],y[i]);
	}

	int ans=0;
	int t[2]={0,0};
	for(t[0]=0;t[0]<4;t[0]++){
		if((t[0]&1)&&l[0]>k) continue ;
		if((t[0]&2)&&r[0]<1) continue ;
		for(t[1]=0;t[1]<4;t[1]++){
			if((t[1]&1)&&l[1]>k) continue ;
			if((t[1]&2)&&r[1]<1) continue ;
			int res=1;
			for(int i=1;i<=k;i++){
				if(cnt[i]==2) MulAs(res,4);
				else if(cnt[i]==1){
					if((t[o[i]^1]&1)&&i<l[o[i]^1]) MulAs(res,2);
					else if((t[o[i]^1]&2)&&i>r[o[i]^1]) MulAs(res,2);
					else MulAs(res,4);
				}
			}
			AddAs(ans,res);
		}
	}

	cout<<ans<<endl;

	for(int i=1;i<=k;i++) cnt[i]=o[i]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}