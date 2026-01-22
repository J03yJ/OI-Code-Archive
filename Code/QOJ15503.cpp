#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int L=3e4;
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
inline int Inv(int x){return QPow(x,mod-2);}

ll a[3],b[3],n;

inline ll Prev(ll x,ll m,ll r){
	ll t=x%m;
	if(t>=r) return x-t+r;
	else return x-t-m+r;
}
inline ll Next(ll x,ll m,ll r){
	ll t=x%m;
	if(t<=r) return x-t+r;
	else return x-t+m+r;
}

const int inv2=mod+1>>1;
inline int F(ll x){return x%=mod,Mul(x,Add(x,1));}
inline int iF(ll x){return Mul(x,Add(x,1));}
inline void LLL(){
	cerr<<"LLL"<<endl;
	ll it[3];
	for(int k:{0,1,2}) it[k]=b[k];
	
	int ans=0;
	ll lst=-1;
	while(true){
		int i=min_element(it,it+3)-it;
		if(it[i]>n){
			AddAs(ans,F(n-lst-1));
			break ;
		}
		AddAs(ans,F(it[i]-lst-1));
		lst=it[i];
		it[i]+=a[i];
	}

	cout<<Mul(ans,inv2)<<endl;
}
inline void SSS(){
	cerr<<"SSS"<<endl;
	ll it[3],lim=1;
	for(int k:{0,1,2}) it[k]=b[k];
	for(int k:{0,1,2}) lim=lim/__gcd(a[k],lim)*a[k];

	if(n<=lim) return LLL();
	
	int ans=0;
	ll lst=*min_element(b,b+3);
	while(true){
		int i=min_element(it,it+3)-it;
		if(it[i]>lim) break ;
		AddAs(ans,F(it[i]-lst-1));
		lst=it[i];
		it[i]+=a[i];
	}

	ll d=n/lim%mod;
	MulAs(ans,d);
	AddAs(ans,Mul(Sub(d,1),F(lim+*min_element(b,b+3)-lst-1)));
	AddAs(ans,F(*min_element(b,b+3)));

	lst+=lim*(n/lim-1);
	for(int k:{0,1,2}) it[k]+=lim*(n/lim-1);
	while(true){
		int i=min_element(it,it+3)-it;
		if(it[i]>n){
			AddAs(ans,F(n-lst-1));
			break ;
		}
		AddAs(ans,F(it[i]-lst-1));
		lst=it[i];
		it[i]+=a[i];
	}

	cout<<Mul(ans,inv2)<<endl;
}
inline void SSL(){
	cerr<<"SSL"<<endl;
	ll it[3],lim=1;
	for(int k:{0,1}) it[k]=b[k];
	for(int k:{0,1}) lim=lim/__gcd(a[k],lim)*a[k];

	if(n<=lim) return LLL();
	
	int ans=0;
	ll lst=*min_element(b,b+2);
	while(true){
		int i=min_element(it,it+2)-it;
		if(it[i]>lim) break ;
		AddAs(ans,iF(it[i]-lst-1));
		lst=it[i];
		it[i]+=a[i];
	}

	ll d=n/lim%mod;
	MulAs(ans,d);
	AddAs(ans,Mul(Sub(d,1),iF(lim+*min_element(b,b+2)-lst-1)));
	AddAs(ans,iF(*min_element(b,b+2)));

	lst+=lim*(n/lim-1);
	for(int k:{0,1}) it[k]+=lim*(n/lim-1);
	while(true){
		int i=min_element(it,it+2)-it;
		if(it[i]>n){
			AddAs(ans,iF(n-lst-1));
			break ;
		}
		AddAs(ans,iF(it[i]-lst-1));
		lst=it[i];
		it[i]+=a[i];
	}

	for(ll x=b[2];x<n;x+=a[2]){
		ll l=max(-1ll,x-a[2]),r=n;
		for(int k:{0,1}){
			l=max(l,Prev(x,a[k],b[k]));
			r=min(r,Next(x,a[k],b[k]));
		}
		SubAs(ans,iF(r-l-1));
		AddAs(ans,iF(r-x-1));
		AddAs(ans,iF(x-l-1));
	}

	cout<<Mul(ans,inv2)<<endl;
}
inline void SLL(){
	cerr<<"SLL"<<endl;
	int ans=0;
	if(n<=b[0]) ans=F(n);
	else{
		ll d=(n-b[0])/a[0]%mod;
		AddAs(ans,F(b[0]));
		AddAs(ans,Mul(d,F(a[0]-1)));
		AddAs(ans,F(n-Prev(n,a[0],b[0])-1));
	}

	ll it[3];
	for(int k:{0,1,2}) it[k]=b[k];
	
	ll lst=-1;
	while(true){
		int i=min_element(it+1,it+3)-it;
		if(it[i]>n) break ;

		ll l=max(-1ll,lst),r=n;
		l=max(l,Prev(it[i],a[0],b[0]));
		r=min(r,Next(it[i],a[0],b[0]));
		SubAs(ans,iF(r-l-1));
		AddAs(ans,iF(r-it[i]-1));
		AddAs(ans,iF(it[i]-l-1));

		lst=it[i];
		it[i]+=a[i];
	}

	cout<<Mul(ans,inv2)<<endl;
}

signed main(){
	cin>>n;
	for(int i:{0,1,2}) cin>>a[i]>>b[i];

	for(int i=0;i<3;i++){
		for(int j=i;j>0;j--){
			if(a[j]<a[j-1]){
				swap(a[j],a[j-1]);
				swap(b[j],b[j-1]);
			}else break ;
		}
	}

	if(a[0]>L) LLL();
	else if(a[1]>L) SLL();
	else if(a[2]>L) SSL();
	else SSS();

	return 0;
}