#include<bits/stdc++.h>

using namespace std;

ifstream fin("template.in");
ofstream fout("template.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int T=60;

struct Node{
	int son[2],mxp;
}tr[N*80];
#define son(x,k) tr[x].son[k]
#define mxp(x) tr[x].mxp

int cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){
	int y=Allc();
	tr[y]=tr[x];
	return y;
}

inline void Insert(int &x,ll k,int id){
	int u=x=Clone(x);
	for(int i=T-1;~i;i--){
		int f=k>>i&1;
		mxp(u)=id;
		son(u,f)=Clone(son(u,f));
		u=son(u,f);
	}
	mxp(u)=id;
}
int root[N],l[N],r[N],m[N],n;
ll a[N],k;

int p[N],mx[N];
inline int Get(int i,int k){return max(mx[i],mxp(son(p[i],a[i]>>k&1)));}
inline void Step(int x,ll val,ll k,ll i){
	if(k>>i&1) mx[x]=max(mx[x],mxp(son(p[x],~(val^k)>>i&1)));
	p[x]=son(p[x],(val^k)>>i&1);
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) Insert(root[i]=root[i-1],a[i],i);

	ll ans=0;
	for(int i=1;i<=n;i++) p[i]=root[i-1];
	for(int i=T-1;~i;i--){
		ll cnt=0;
		for(int j=1;j<=n;j++){
			m[j]=max(m[j-1],Get(j,i));
			cnt+=m[j];
		}
		if(k>cnt) ans|=1ll<<i;
		for(int j=1;j<=n;j++) Step(j,a[j],ans,i);
	}

	cout<<ans<<endl;

	return 0;
}