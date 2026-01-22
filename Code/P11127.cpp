#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;
const int S=4e2+9;

int lc[N],rc[N],fa[N],id[N],dfn[N],siz[N],t[N],n,q,icnt,dcnt;
inline void GetId(int x){
	if(!x) return ;
	dfn[x]=++dcnt;
	fa[lc[x]]=fa[rc[x]]=x;
	t[lc[x]]=t[x];
	GetId(lc[x]);
	id[x]=++icnt;
	t[rc[x]]=t[x]+siz[lc[x]];
	GetId(rc[x]);
	siz[x]=siz[lc[x]]+siz[rc[x]]+1;
}

int blk[N],p[N],L[N],R[N],upl[N],upr[N],w[N],c[N],tag[S],lst[N][S],B;
inline void GetLast(int x){
	if(!x) return ;
	for(int i=1;i<=blk[n];i++) lst[x][i]=lst[fa[x]][i];
	lst[x][blk[x]]=x;
	GetLast(lc[x]),GetLast(rc[x]);
}

inline void Build(int x){
	for(int i=L[x];i<=R[x];i++){
		int u=p[i],f=lst[fa[u]][x];
		if(!f){
			w[u]=0;
			continue ;
		}
		w[u]=w[f];
		if(id[u]<id[f]&&c[f]<0) w[u]++;
		if(id[u]>id[f]&&c[f]<=0) w[u]++;
	}
}
inline void PushTag(int x,int k){tag[x]=k;}
inline void PushDown(int x){
	if(tag[x]==-2) return ;
	for(int i=L[x];i<=R[x];i++) c[i]=tag[x];
	tag[x]=-2;
}
inline void BAssign(int l,int r,int k){
	PushDown(blk[l]);
	for(int i=l;i<=r;i++) c[i]=k;
	Build(blk[l]);
}
inline void Assign(int l,int r,int k){
	if(blk[l]==blk[r]) return BAssign(l,r,k);
	BAssign(l,R[blk[l]],k),BAssign(L[blk[r]],r,k);
	for(int i=blk[l]+1;i<blk[r];i++) PushTag(i,k);
}
inline int GetW(int p){
	if(tag[blk[p]]==-2) return w[p];
	else{
		if(tag[blk[p]]==-1) return upl[p]+upr[p];
		else if(tag[blk[p]]==0) return upr[p];
		else return 0;
	}
}
inline int GetC(int p){return tag[blk[p]]==-2?c[p]:tag[blk[p]];}
inline int Query(int x){
	int ans=t[x];
	if(GetC(x)==-1) ans+=1;
	else if(GetC(x)==0) ans+=siz[lc[x]]+1;
	else if(GetC(x)==1) ans+=siz[lc[x]]+siz[rc[x]]+1;
	for(int i=1;i<=blk[n];i++){
		int u=lst[x][i];
		if(!u) continue ;
		ans+=GetW(u);
		if(u==x) continue ;
		if(id[x]<id[u]&&GetC(u)<0) ans++;
		if(id[x]>id[u]&&GetC(u)<=0) ans++;
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>lc[i]>>rc[i];
	GetId(1);

	B=sqrt(n);
	for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
	for(int i=1;i<=n;i++) R[blk[i]]=i;
	for(int i=n;i>=1;i--) L[blk[i]]=i;
	for(int i=1;i<=n;i++){
		for(int j=L[i];j<=R[i];j++) p[j]=j;
		sort(p+L[i],p+R[i]+1,[](int i,int j){return dfn[i]<dfn[j];});
	}
	GetLast(1);
	for(int i=1;i<=blk[n];i++){
		for(int j=L[i];j<=R[i];j++){
			int u=p[j],f=lst[fa[u]][i];
			if(!f) continue ;
			upl[u]=upl[f],upr[u]=upr[f];
			if(id[u]<id[f]) upl[u]++;
			else upr[u]++;
		}
		tag[i]=-2;
	}
	for(int i=1;i<=n;i++) c[i]=-1,w[i]=upl[i]+upr[i];

	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int l,r,x;
			cin>>l>>r>>x;
			Assign(l,r,x);
		}else{
			int u;
			cin>>u;
			cout<<Query(u)<<endl;
		}
	}

	return 0;
}