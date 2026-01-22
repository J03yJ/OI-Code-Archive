#include<bits/stdc++.h>

using namespace std;

ifstream fin("party.in");
ofstream fout("party.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int mod=147744151;

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

const int N=2e5+9;

int /* f[N][N], */p[N];
vector<array<int,2>> op[N];

struct Node{
	int l,r;
	int dat,tag,clr;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag
#define clr(x) tr[x].clr
#define len(x) (r(x)-l(x)+1)

inline void PushUp(int x){dat(x)=Add(dat(x<<1),dat(x<<1|1));}
// inline void PushAdd(int x,int k){AddAs(tag(x),k),AddAs(dat(x),Mul(len(x),k));}
inline void PushClr(int x){clr(x)=1,tag(x)=dat(x)=0;}
inline void PushDown(int x){
	if(clr(x)) PushClr(x<<1),PushClr(x<<1|1),clr(x)=0;
	// if(tag(x)) PushAdd(x<<1,tag(x)),PushAdd(x<<1|1,tag(x)),tag(x)=0;
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,dat(x)=tag(x)=clr(x)=0;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline int Get(int x,int pos){
	if(l(x)==r(x)) return dat(x);
	PushDown(x);
	int mid=l(x)+r(x)>>1;
	if(pos<=mid) return Get(x<<1,pos);
	else return Get(x<<1|1,pos);
}
inline void Set(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)+=k,void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		bool flag=0;
		for(int i=1;i<=m;i++){
			ll x;
			cin>>x;
			int a=(x-1)/n+1,b=(x-1)%n+1;
			if(!p[a]||p[a]==b) p[a]=b;
			else flag=1;
		}
		if(flag){
			cout<<0<<endl;
			for(int i=1;i<=n;i++) p[i]=0;
			continue ;
		}
		
		// f[0][1]=1;
		// for(int i=1;i<=n;i++){
		// 	for(int j=1;j<=i;j++){
		// 		if(!p[i]||p[i]==j) AddAs(f[i][i+1],f[i-1][j]);
		// 		if(!p[i]||p[i]==i+1) AddAs(f[i][j],f[i-1][j]);
		// 		if((!p[i]||p[i]==i+2)&&(!p[i+1]||p[i+1]==j)) AddAs(f[i+1][i+1],f[i-1][j]);
		// 	}
		// }

		Build(1,1,n+1);
		Set(1,1,1);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n+1;j++) cout<<Get(1,j)<<' ';cout<<endl;
			if(!p[i]) op[i].push_back({i+1,dat(1)});
			else op[i].push_back({i+1,Get(1,p[i])});
			if(!p[i]||p[i]==i+2){
				if(!p[i+1]) op[i+1].push_back({i+1,dat(1)});
				else op[i].push_back({i+1,Get(1,p[i+1])});
			}
			if(!(!p[i]&&p[i]==i+1)) PushClr(1);
			for(auto t:op[i]) Set(1,t[0],t[1]),cout<<" -> "<<t[0]<<' '<<t[1]<<endl;;
		}
		for(int j=1;j<=n+1;j++) cout<<Get(1,j)<<' ';cout<<endl;

		cout<<Get(1,n+1)<<endl;

		for(int i=1;i<=n;i++) p[i]=0,op[i].clear();
		// for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) f[i][j]=0;
	}

	return 0;
}