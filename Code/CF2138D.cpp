#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e3+9;
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

int fac[N],ifac[N],d[N],p[N],t[N],o[N],n,m,q;
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}
inline int MutC(initializer_list<int> v){
	int res=1,sum=0;
	for(int x:v){
		if(x<0) return 0;
		MulAs(res,ifac[x]),sum+=x;
	}
	return Mul(fac[sum],res);
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++) cin>>d[i];
		for(int i=1;i<=q;i++) cin>>p[i]>>t[i],o[i]=i;
		
		Init(q);
		sort(o+1,o+q+1,[](int i,int j){return t[i]-p[i]<t[j]-p[j];});
		for(int i=1;i<=n;i++){
			int ans=0;
			vector<int> a,b,c;
			for(int j=1;j<=q;j++){
				int k=o[j];
				if(p[k]>i) a.push_back(t[k]+i-p[k]);
				else if(p[k]<i) b.push_back(t[k]+i-p[k]);
				else c.push_back(t[k]);
			}
			vector<int> val;
			for(auto v:{&a,&b,&c}) val.insert(val.end(),v->begin(),v->end());
			sort(val.begin(),val.end());
			val.erase(unique(val.begin(),val.end()),val.end());
			if(!c.size()){
				if((!a.size()||!b.size()||a.front()>b.back())){
					int pos=d[i];
					if(a.size()) pos=min(pos,a.front());
					if(b.size()) pos=max(pos,b.back());
					ans=Mul(pos,fac[q]);
					cout<<ans<<' ';
					continue ;
				}
			}
			for(int j=0,al=0,ar=0,bl=0,br=0,cl=0,cr=0;j<val.size();j++){
				int x=val[j];
				auto Count=[](vector<int> &a,int &al,int &ar,int x)->array<int,3>{
					while(al<a.size()&&a[al]<x) al++;
					while(ar<a.size()&&a[ar]<=x) ar++;
					return {al,ar-al,a.size()-ar};
				};
				array<int,3> A=Count(a,al,ar,x);
				array<int,3> B=Count(b,bl,br,x);
				array<int,3> C=Count(c,cl,cr,x);
				int cnt=0;
				SubAs(cnt,Mul(Mul(Mul(MutC({A[0],C[0]}),MutC({B[1],B[2],C[1],C[2]})),
				MutC({A[0]+C[0]-1,B[1]+B[2]+C[1]+C[2]})),
				MutC({A[0]+B[1]+B[2]+C[0]+C[1]+C[2],A[1],A[2],B[0]})));
				SubAs(cnt,Mul(Mul(Mul(MutC({B[2],C[2]}),MutC({A[0],A[1],C[0],C[1]})),
				MutC({B[2]+C[2]-1,A[0]+A[1]+C[0]+C[1]})),
				MutC({A[0]+A[1]+B[2]+C[0]+C[1]+C[2],A[2],B[0],B[1]})));
				for(int y:{A[0],A[1],A[2],B[0],B[1],B[2],C[0],C[1],C[2]}) MulAs(cnt,fac[y]);
				AddAs(cnt,fac[q]);
				AddAs(ans,Mul(x,cnt));
			}
			cout<<ans<<' ';
		}
		cout<<endl;
	}

	return 0;
}