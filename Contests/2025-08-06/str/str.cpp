#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

ifstream fin("str.in");
ofstream fout("str.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

template<int mod,int base,bool rev> struct Hash{
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

	int n;
	vector<int> h,b,ib;
	inline void Init(string s){
		if(rev) reverse(s.begin(),s.end());
		s="#"+s;
		n=s.size()-1;
		h=b=ib=vector<int>(s.size(),0);
		b[0]=ib[0]=1;
		b[1]=base,ib[1]=Inv(base);
		for(int i=1;i<s.size();i++){
			b[i]=Mul(b[i-1],b[1]);
			ib[i]=Mul(ib[i-1],ib[1]);
			h[i]=Add(h[i-1],Mul(b[i-1],s[i]));
		}
	}
	inline int FH(int l,int r){return Mul(ib[l-1],Sub(h[r],h[l-1]));}
	inline int BH(int l,int r){return FH(n-r+1,n-l+1);}
	inline int H(int l,int r){return !rev?FH(l,r):BH(l,r);}
	inline void Clear(){
		h.clear();
		h.shrink_to_fit();
		b.clear();
		b.shrink_to_fit();
		ib.clear();
		ib.shrink_to_fit();
	}
};
template<bool rev> struct DHash{
	Hash<998244353,4649,rev> h0;
	Hash<1000000007,131,rev> h1;
	inline void Init(string s){h0.Init(s),h1.Init(s);}
	inline ll H(int l,int r){return ll(h0.H(l,r))<<32|ll(h1.H(l,r));}
	inline void Clear(){h0.Clear(),h1.Clear();}
};

int n,m;
string s[N],t[N];
DHash<0> hs[N],ht[N];
DHash<1> rs[N],rt[N];
inline int Limit(int x){return x?__lg(x):-1;}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>s[i];
		for(int i=1;i<=m;i++) cin>>t[i];

		for(int i=1;i<=n;i++){
			hs[i].Init(s[i]);
			rs[i].Init(s[i]);
			s[i]="#"+s[i];
		}
		for(int i=1;i<=m;i++){
			ht[i].Init(t[i]);
			rt[i].Init(t[i]);
			t[i]="#"+t[i];
		}

		gp_hash_table<ll,int> ms,vis;
		for(int i=1;i<=n;i++){
			int tot=s[i].size()-1;
			for(int j=tot;j>=1;j--) ms[rs[i].H(j,tot)]++;
		}
		for(int i=1;i<=n;i++){
			int tot=s[i].size()-1;
			for(int j=tot;j>=1;j--){
				if(vis[rs[i].H(j,tot)]) continue ;
				vis[rs[i].H(j,tot)]=1;
				ms[rs[i].H(j,tot)]+=ms[rs[i].H(j+1,tot)];
			}
		}
		gp_hash_table<ll,int> mt,vit;
		for(int i=1;i<=m;i++){
			int tot=t[i].size()-1;
			for(int j=1;j<=tot;j++) mt[ht[i].H(1,j)]++;
		}
		for(int i=1;i<=m;i++){
			int tot=t[i].size()-1;
			for(int j=1;j<=tot;j++){
				if(vit[ht[i].H(1,j)]) continue ;
				vit[ht[i].H(1,j)]=1;
				mt[ht[i].H(1,j)]+=mt[ht[i].H(1,j-1)];
			}
		}

		ll ans=0;
		for(int i=1;i<=n;i++){
			int tot=s[i].size()-1;
			for(int j=1;j<=tot;j++){
				int len=0;
				for(int k=Limit(min(j-1,tot-j));~k;k--){
					len|=1<<k;
					if(j-len<1||j+len>tot) len^=1<<k;
					else if(hs[i].H(j-len,j)!=rs[i].H(j,j+len)) len^=1<<k;
				}
				ans+=1ll*(len+1)*m;
				if(j+len!=tot) continue ;
				int nel=0;
				for(int k=Limit(j-len-1);~k;k--){
					nel|=1<<k;
					if(j-len-nel<1) nel^=1<<k;
					else if(!vit[rs[i].H(j-len-nel,j-len-1)]) nel^=1<<k;
				}
				ans+=mt[rs[i].H(j-len-nel,j-len-1)];
			}
		}
		for(int i=1;i<=n;i++){
			int tot=t[i].size()-1;
			for(int j=1;j<=tot;j++){
				int len=0;
				for(int k=Limit(min(j-1,tot-j));~k;k--){
					len|=1<<k;
					if(j-len<1||j+len>tot) len^=1<<k;
					else if(ht[i].H(j-len,j)!=rt[i].H(j,j+len)) len^=1<<k;
				}
				ans+=1ll*(len+1)*n;
				if(j-len!=1) continue ;
				int nel=0;
				for(int k=Limit(tot-j-len);~k;k--){
					nel|=1<<k;
					if(j+len+nel>tot) nel^=1<<k;
					else if(!vis[ht[i].H(j+len+1,j+len+nel)]) nel^=1<<k;
				}
				ans+=ms[ht[i].H(j+len+1,j+len+nel)];
			}
		}

		cout<<ans<<endl;

		ms.clear();
		mt.clear();
		vis.clear();
		vit.clear();
		for(int i=1;i<=n;i++) hs[i].Clear(),ht[i].Clear();
		for(int i=1;i<=m;i++) rs[i].Clear(),rt[i].Clear();
	}

	return 0;
}