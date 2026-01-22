#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using ull=unsigned long long;
using bint=__int128;
const int N=2e6+9;
const int K=1e3+9;
const int lgN=2e1;
const ll mod=114514191981000001ll;
const ll base=1000;

inline void AddAs(ll &x,ll y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(ll &x,ll y){if((x-=y)<0) x+=mod;}
inline void MulAs(ll &x,ll y){x=bint(x)*y%mod;}
inline ll Add(ll x,ll y){if((x+=y)>=mod) x-=mod;return x;}
inline ll Sub(ll x,ll y){if((x-=y)<0) x+=mod;return x;}
inline ll Mul(ll x,ll y){return bint(x)*y%mod;}
inline ll QPow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline ll Inv(ll x){return QPow(x,mod-2);}

int n,m,k;
char s[N],t[N];
ll hs[N],ht[N],b[N],ib[N];
inline void Init(int lim){
	const ll ibase=Inv(base);
	ib[0]=b[0]=1;
	for(int i=1;i<=lim;i++){
		b[i]=Mul(b[i-1],base);
		ib[i]=Mul(ib[i-1],ibase);
	}
}
inline void CalcHash(char *s,ll *h,int n){
	for(int i=1;i<=n;i++) h[i]=Add(h[i-1],Mul(s[i],b[i-1]));
}
inline ll H(ll *h,int l,int r){return Mul(Sub(h[r],h[l-1]),ib[l-1]);}
inline int LCP(int i,int j){
	int l=0,r=min(n-i+1,m-j+1)+1;
	while(l+1<r){
		int mid=l+r>>1;
		if(H(hs,i,i+mid-1)==H(ht,j,j+mid-1)) l=mid;
		else r=mid;
	}
	return l;
}

int cnt=0;
const int dx[3]={1,0,1};
const int dy[3]={0,1,1};
int id[K][K<<1],pre[K][K<<1];
inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=m;i++) cin>>t[i];

	Init(max(n,m));
	CalcHash(s,hs,n);
	CalcHash(t,ht,m);
	
	auto T=[](array<int,2> p)->array<int,2>{
		int k=LCP(p[0],p[1]);
		return {p[0]+k,p[1]+k};
	};
	for(int i=0;i<=k;i++){
		for(int j=-k;j<=k;j++) id[i][K+j]=pre[i][K+j]=-1;
	}
	int p=-1;
	id[0][K+0]=1+LCP(1,1);
	for(int r=0;r<=k;r++){
		for(int d=-k;d<=k;d++){
			int i=id[r][K+d],j=i-d;
			if(!~i) continue ;
			if(i==n+1&&j==m+1){
				p=r;
				break ;
			}
			for(int o:{0,1,2}){
				if(i+dx[o]>n+1||j+dy[o]>m+1) continue ;
				array<int,2> nxt=T({i+dx[o],j+dy[o]});
				int u=nxt[0],v=nxt[1];
				if(u>id[r+1][K+u-v]){
					id[r+1][K+u-v]=u;
					pre[r+1][K+u-v]=i-j;
				}
			}
		}
		if(~p) break ;
	}

	if(~p){
		cout<<"YES"<<endl;
		cout<<p<<endl;
		vector<tuple<string,int,char>> ans;
		for(int r=p,i=n+1,j=m+1;r>=1;r--){
			int u=id[r-1][K+pre[r][K+i-j]],v=u-pre[r][K+i-j];
			if(!~u) break ;
			int dlt=(i-u)-(j-v);
			if(dlt==0) ans.push_back({"REPLACE",v,t[v]});
			else if(dlt==1) ans.push_back({"DELETE",v,'#'});
			else ans.push_back({"INSERT",v,t[v]});
			i=u,j=v;
		}
		reverse(ans.begin(),ans.end());
		for(auto t:ans){
			if(get<0>(t)=="DELETE") cout<<get<0>(t)<<' '<<get<1>(t)<<endl;
			else cout<<get<0>(t)<<' '<<get<1>(t)<<' '<<get<2>(t)<<endl;
		}
	}else cout<<"NO"<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}