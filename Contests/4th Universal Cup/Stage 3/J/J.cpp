#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;

int p[N],n;

array<ll,2> tr[N];
inline void Add(int x,array<ll,2> k){while(x<=n) tr[x]=max(tr[x],k),x+=x&-x;}
inline array<ll,2> Ask(int x){array<ll,2> res={0,0};while(x) res=max(res,tr[x]),x&=x-1;return res;}
inline void Clear(){for(int i=1;i<=n;i++) tr[i]={0,0};}

inline int GetP(int k){
	for(int i=1;i<=n;i++){
		array<ll,2> s=Ask(p[i]),t=Ask(n);
		Add(p[i],{s[0]+1,s[1]});
		Add(p[i],{t[0]+1-k,t[1]+1});
	}
	array<ll,2> s=Ask(n);
	Clear();
	return s[1]+1;
}

int k[N],f[N];
inline void Work(int l,int r){
	if(l>r) return ;
	if(k[l-1]==k[r+1]){
		for(int i=l;i<=r;i++) k[i]=k[l-1];
		return ;
	}
	int mid=l+r>>1;
	k[mid]=GetP(mid);
	Work(l,mid-1),Work(mid+1,r);
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];

	k[0]=n+1,k[n+1]=0;
	Work(1,n);
	for(int i=0;i<n;i++){
		for(int j=k[i+1];j<k[i];j++) f[j]=i;
	}
	f[n]=n;
	for(int i=n-1;i>=1;i--) f[i]=f[i+1]-f[i];

	for(int i=1;i<=n;i++) cout<<f[i]<<' ';cout<<endl;
	for(int i=0;i<=n+1;i++) f[i]=k[i]=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}