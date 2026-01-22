#include<bits/stdc++.h>

using namespace std;

using ll=long long;
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

// inline bool Check(vector<int> v){
// 	int n=v.size();
// 	for(int l=0;l<n;l++){
// 		for(int r=l;r<n;r++){
// 			int cnt=0;
// 			for(int k=l;k<=r;k++){
// 				if(v[k]==k) continue ;
// 				if(v[k]<l||v[k]>r) continue ;
// 				cnt++;
// 			}
// 			if(cnt<r-l) return 0;
// 		}
// 	}
// 	return 1;
// }
// inline void DFS(int n,int m,vector<int> v){
// 	if(!n){
// 		if(Check(v)){
// 			for(int x:v) cout<<x+1<<' ';
// 			cout<<endl;
// 		}
// 		return ;
// 	}
// 	for(int i=0;i<m;i++){
// 		v.push_back(i);
// 		DFS(n-1,m,v);
// 		v.pop_back();
// 	}
// }

signed main(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int &x:a) cin>>x;

	vector<int> f(n,0),g(n,0),h(n,0);
	for(int i=0;i<n;i++){
		if(i){
			f[i]=(a[i-1]==-1)||(a[i-1]==i+1);
			f[i]&=f[i-1];
		}else f[i]=1;
	}
	for(int i=n-1;~i;i--){
		if(i+1<n){
			g[i]=(a[i+1]==-1)||(a[i+1]==i+1);
			g[i]&=g[i+1];
		}else g[i]=1;
	}
	for(int i=0;i<n;i++) h[i]=f[i]&g[i];

	int ans=0;
	for(int i=0;i<n;i++) if(h[i]) AddAs(ans,a[i]==-1?n:1);
	for(int i=0;i+1<n;i++) if(h[i]&&h[i+1]) SubAs(ans,1);

	cout<<ans<<endl;

	return 0;
}