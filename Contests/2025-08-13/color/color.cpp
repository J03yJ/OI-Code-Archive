#include<bits/stdc++.h>

using namespace std;

ifstream fin("color.in");
ofstream fout("color.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=2e5+9;

int fa[N<<1];
inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline int Merge(int x,int y){
	if(!x||!y) return x|y;
	else return fa[Find(y)]=Find(x);
}

int xl[N],xr[N],yl[N],yr[N],p[N<<1],n;

int tr[N<<1];
inline void Add(int x,int k){while(x<=(n<<1)) tr[x]+=k,x+=x&-x;}
inline void Add(int l,int r,int k){Add(l,k),Add(r+1,k);}
inline int Ask(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}

struct Seg{
	int l,r,v;
	Seg(){}
	Seg(int _l,int _r,int _v){l=_l,r=_r,v=_v;}
	inline bool operator <(Seg s){return l<s.l;}
};

set<Seg> odt;
inline auto Split(int pos){
	auto it=odt.upper_bound(Seg(pos,0,0));
	if(it==odt.end()||it->l==pos) return it;
	Seg s=*it;
	odt.erase(it);
	odt.insert(Seg(s.l,pos-1,s.v));
	return odt.insert(Seg(pos,s.r,s.v)).first;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>xl[i]>>yl[i]>>xr[i]>>yr[i];

	Init(n<<1);

	for(int i=1;i<=(n<<1);i++) cout<<Find(i)<<' ';cout<<endl;
	for(int i=1;i<=n;i++) if(Find(i)==Find(i+n)) cout<<"ERR"<<endl;

	return 0;
}