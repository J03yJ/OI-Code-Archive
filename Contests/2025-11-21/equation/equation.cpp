#include<bits/stdc++.h>

using namespace std;

ifstream fin("equation.in");
ofstream fout("equation.out");
#define cin fin
#define cout fout
#define endl '\n'

using bint=__int128;
using ll=long long;
const int N=1e5+9;
const ll AMB=123456797654321ll;
const ll IMP=976543212345679ll;
const ll SUC=515472268187439ll;

struct F{
	ll k,b;
	F(ll _k=0,ll _b=0){k=_k,b=_b;}
	inline F operator ()(F f){return F(k*f.k,k*f.b+b);}
	inline ll operator ()(ll x){return k*x+b;}
	inline F Inv(){return F(1/k,-b/k);}
};

F tag[N];
ll val[N],M,V;
int fa[N],siz[N],n,q,err;
inline void Init(){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,tag[i]=F(1,0),val[i]=LLONG_MAX;err=0;}
inline int Find(int x){return x==fa[x]?x:Find(fa[x]);}
inline F Sum(int x){return x==fa[x]?tag[x]:tag[x](Sum(fa[x]));}
inline void Merge(int x,int y,ll v){
	F fx=Sum(x),fy=Sum(y);
	x=Find(x),y=Find(y);
	if(x==y){
		if(fx.k==-fy.k){
			if(fx.b+fy.b!=v) err=1;
		}else{
			if((v-fx.b-fy.b)%(fx.k+fy.k)) err=1;
			else{
				ll tmp=(v-fx.b-fy.b)/(fx.k+fy.k);
				if(val[x]==LLONG_MAX) val[x]=tmp;
				else if(val[x]!=tmp) err=1;
			}
		}
	}else{
		if(siz[x]<siz[y]) swap(x,y),swap(fx,fy);
		tag[y]=F(-fx.k/fy.k,(v-fy.b-fx.b)/fy.k);
		fa[y]=x;
		siz[x]+=siz[y];
		if(val[y]!=LLONG_MAX){
			ll tmp=Sum(y).Inv()(val[y]);
			if(val[x]==LLONG_MAX) val[x]=tmp;
			else if(val[x]!=tmp) err=1;
		}
	}
}

inline void Solve(){
	cin>>n>>q;
	ll L=0;
	Init();
	while(q--){
		ll t,x,y,v;
		cin>>t>>x>>y>>v;
		t=(t+bint(M)*L%2+2)%2;
		x=(x+bint(M)*L%n-1+n)%n+1;
		y=(y+bint(M)*L%n-1+n)%n+1;
		v=(v+bint(M)*L%(V+1)+V+1)%(V+1);

		if(t==0) Merge(x,y,v);
		else if(t==1){
			if(err){
				cout<<"Impossible"<<endl;
				L=IMP;
				continue ;
			}
			if(val[Find(x)]!=LLONG_MAX){
				if(Sum(x)(val[Find(x)])!=v){
					cout<<"Impossible"<<endl;
					L=IMP;
					continue ;
				}
			}
			if(Find(x)==Find(y)){
				ll r=Sum(x).Inv()(v),ans=Sum(y)(r);
				cout<<ans<<endl;
				L=SUC+ans;
			}else{
				if(val[Find(y)]!=LLONG_MAX){
					ll ans=Sum(y)(val[Find(y)]);
					cout<<ans<<endl;
					L=SUC+ans;
				}else{
					cout<<"Ambiguous"<<endl;
					L=AMB;
				}
			}
		}
	}
}

signed main(){
	int T;
	cin>>T>>M>>V;
	while(T--) Solve();

	return 0;
}