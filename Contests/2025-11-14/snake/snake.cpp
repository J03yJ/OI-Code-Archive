#include<bits/stdc++.h>

using namespace std;

ifstream fin("snake.in");
ofstream fout("snake.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int mod=1e9+7;

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

int a[N],n,k;
inline vector<int> Shift(vector<int> v,int k){
	vector<int> tmp(v.begin()+k,v.end());
	tmp.insert(tmp.end(),v.begin(),v.begin()+k);
	return tmp;
}

inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		a[i]=c=='?'?-1:c=='x';
	}

	int ans=0,c=0;
	vector<int> cnt(k,0);
	for(int i=1;i<=n;i++){
		if(!~a[i]||!~cnt[i%k]) cnt[i%k]=-1;
		else cnt[i%k]^=a[i];
	}
	for(int i=0;i<k;i++) if(!~cnt[i%k]) c++;
	for(int i=n;i>=k;i-=k) AddAs(ans,QPow(2,i-k+min(k,c+1)));

	int cur=0;
	for(int i=n%k+1;i<=k;i++) cur|=cnt[i%k]+1;
	if(cur<3){
		int d=cur==0/* ||cur<3&&(n/k&1) */;
		for(int i=1;i<=n%k;i++) d+=cnt[i]==-1;
		d=min(d,n%k);
		AddAs(ans,QPow(2,d));
	}

	cout<<ans<<endl;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}