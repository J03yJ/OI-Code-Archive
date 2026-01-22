#include<bits/stdc++.h>

using namespace std;

ifstream fin("hacho.in");
ofstream fout("hacho.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Mod(ll x){return Add(x%mod,mod);}

int a[N],p[N],n;
ll s[N],k;
inline ll MaxSubseq(){
	ll mxsum=-1e18,sum=0;
	for(int i=1;i<=n;i++){
		sum=a[i]+max(sum,0ll);
		mxsum=max(mxsum,sum);
	}
	return mxsum;
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=0;
	SubAs(ans,Mod(MaxSubseq()));
	while(k){
		ll sum=0,mxsum=-1e18;
		for(int i=n;i>=1;i--){
			if(sum>0){
				p[i]=p[i+1];
				sum+=a[i];
			}else{
				p[i]=i;
				sum=a[i];
			}
			mxsum=max(mxsum,sum);
		}
		int cnt=0;
		for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		for(int i=1,pos=n+1;i<=n&&cnt<k;i++){
			if(s[p[i]]-s[i-1]==mxsum) pos=min(pos,p[i]);
			if(pos==i) a[i]--,cnt++,pos=n+1;
		}
		cnt=min(ll(cnt),k);
		AddAs(ans,Mul(cnt,Mod(mxsum)));
		k-=cnt;
	}
	AddAs(ans,Mod(MaxSubseq()));
	
	cout<<ans<<endl;

	return 0;
}