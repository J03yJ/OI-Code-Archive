#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e5+9;

struct Basis{
	int b[30],cnt;
	inline void Insert(int x,int p=29){
		for(int i=p;~i;i--){
			if(~x>>i&1) continue ;
			if(!b[i]){
				b[i]=x;
				cnt++;
				break ;
			}else x^=b[i];
		}
	}
	inline int Max(int x){
		for(int i=29;~i;i--) if((x^b[i])>x) x^=b[i];
		return x;
	}
	inline void Merge(Basis &y){
		if(cnt==30) return ;
		for(int i=0;i<30;i++) if(y.b[i]) Insert(y.b[i],i);
	}
	inline void Clear(){memset(b,0,sizeof b),cnt=0;}
}b[N];
int fa[N],siz[N],tag[N];
vector<pair<int&,int>> rcll;
vector<pair<Basis&,Basis>> bcll;
inline void Init(int n){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,tag[i]=0,b[i].Clear();}
inline int Find(int x){return fa[x]==x?x:Find(fa[x]);}
inline int WTop(int x){return fa[x]==x?tag[x]:tag[x]^WTop(fa[x]);}
inline void Merge(int x,int y,int w,bool rec){
	int u=Find(x),v=Find(y);
	if(u==v){
		if(rec) bcll.push_back({b[u],b[u]});
		b[u].Insert(WTop(x)^WTop(y)^w);
	}else{
		if(siz[u]<siz[v]) swap(u,v),swap(x,y);
		if(rec){
			bcll.push_back({b[u],b[u]});
			rcll.push_back({fa[v],fa[v]});
			rcll.push_back({siz[u],siz[u]});
			rcll.push_back({tag[v],tag[v]});
		}
		tag[v]^=WTop(x)^WTop(y)^w;
		fa[v]=u;
		siz[u]+=siz[v];
		b[u].Merge(b[v]);
	}
}
inline void Recall(int bc,int rc){
	while(bcll.size()>bc) bcll.back().first=bcll.back().second,bcll.pop_back();
	while(rcll.size()>rc) rcll.back().first=rcll.back().second,rcll.pop_back();
}

vector<int> qry[N];
int eu[N],ev[N],ew[N],ql[N],qr[N],qu[N],qv[N],ans[N],blk[N],L[N],R[N],n,m,q,B;

signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) cin>>eu[i]>>ev[i]>>ew[i];
	for(int i=1;i<=q;i++) cin>>ql[i]>>qr[i]>>qu[i]>>qv[i];

	B=sqrt(m);
	for(int i=1;i<=m;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=m;i++) R[blk[i]]=i;
	for(int i=m;i>=1;i--) L[blk[i]]=i;

	for(int i=1;i<=q;i++) qry[blk[ql[i]]].push_back(i);

	for(int i=1;i<=blk[m];i++){
		Init(n);
		int l=R[i]+1,r=R[i];
		sort(qry[i].begin(),qry[i].end(),[](int p,int q){return qr[p]<qr[q];});
		for(int j:qry[i]){
			if(blk[qr[j]]==i){
				for(int k=ql[j];k<=qr[j];k++) Merge(eu[k],ev[k],ew[k],1);
				if(Find(qu[j])!=Find(qv[j])) ans[j]=-1;
				else ans[j]=b[Find(qu[j])].Max(WTop(qu[j])^WTop(qv[j]));
				Recall(0,0);
				continue ;
			}
			while(r<qr[j]) r++,Merge(eu[r],ev[r],ew[r],0);
			while(l>ql[j]) l--,Merge(eu[l],ev[l],ew[l],1);
			if(Find(qu[j])!=Find(qv[j])) ans[j]=-1;
			else ans[j]=b[Find(qu[j])].Max(WTop(qu[j])^WTop(qv[j]));
			Recall(0,0);
			l=R[i]+1;
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}