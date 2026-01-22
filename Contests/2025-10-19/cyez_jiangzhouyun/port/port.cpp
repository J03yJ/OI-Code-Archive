#include<bits/stdc++.h>

using namespace std;

ifstream fin("port.in");
ofstream fout("port.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e6+9;
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

int a[N],b[N],n,m,k;
inline int NoCon(){
	int ans=0;
	AddAs(ans,Mul(n%m,QPow(m,n/m+1)));
	AddAs(ans,Mul(m-(n%m),QPow(m,n/m)));
	MulAs(ans,2);
	SubAs(ans,Mul(m,m));
	return ans;
}
inline int CalcRow(){
	vector<int> val;
	for(int i=1;i<=k;i++) val.push_back(a[i]);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=0;i+1<val.size();i++) if((val[i+1]-val[i])%m) return 0;
	map<int,int> mp;
	for(int i=1;i<=k;i++){
		if(mp[a[i]]&&mp[a[i]]!=b[i]%m) return 0;
		mp[a[i]]=b[i]%m;
	}
	int cnt=(n-((val.front()-1)%m+1))/m+1;
	return QPow(m,cnt-mp.size());
}
inline int CheckSame(){
	vector<array<int,2>> val;
	for(int i=1;i<=k;i++) val.push_back({a[i]%m,b[i]%m});
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	return val.size()==1;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=k;i++) cin>>a[i]>>b[i];

		if(!k){
			cout<<NoCon()<<endl;
			continue ;
		}

		int ans=0;
		AddAs(ans,CalcRow());
		for(int i=1;i<=k;i++) swap(a[i],b[i]);
		AddAs(ans,CalcRow());
		SubAs(ans,CheckSame());

		cout<<ans<<endl;
	}

	return 0;
}