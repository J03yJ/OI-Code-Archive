#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e6+9;
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
inline int Inv(int x){return QPow(x,mod-2);}

vector<int> e[N],o[N];
int u[N],v[N],c[N],cnt[N],col[N],n,m;

int fa[N],vsiz[N],esiz[N];
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	fa[y]=x;
	vsiz[x]+=vsiz[y];
	esiz[x]+=esiz[y];
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>c[i];

	for(int i=1;i<=m;i++){
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
		o[c[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(o[i].size()<2) continue ;
		vector<int> node;
		for(int j:o[i]){
			cnt[u[j]]++;
			cnt[v[j]]++;
			node.push_back(u[j]);
			node.push_back(v[j]);
		}
		sort(node.begin(),node.end());
		node.erase(unique(node.begin(),node.end()),node.end());
		int p=0;
		for(int j:node){
			if(cnt[j]!=o[i].size()) continue ;
			if(!p) p=j;
			else p=-1;
		}
		if(!p){
			cout<<0<<endl;
			return 0;
		}
		if(~p) col[p]=i;
		for(int j:o[i]) cnt[u[j]]--,cnt[v[j]]--;
	}

	queue<int> q;
	for(int i=1;i<=n;i++) if(col[i]) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i:e[x]){
			int y=x^u[i]^v[i];
			if(col[y]){
				if(col[x]!=c[i]&&col[y]!=c[i]){
					cout<<0<<endl;
					return 0;
				}
			}else{
				if(col[x]!=c[i]){
					col[y]=c[i];
					q.push(y);
				}
			}
		}
	}

	for(int i=1;i<=n;i++) fa[i]=i,vsiz[i]=!col[i];
	for(int i=1;i<=m;i++){
		if(col[u[i]]||col[v[i]]) continue ;
		Merge(u[i],v[i]);
		esiz[Find(u[i])]++;
	}

	int ans=1,cnt=0;
	for(int i=1;i<=n;i++){
		if(col[i]) continue ;
		if(fa[i]!=i) continue ;
		if(esiz[i]>vsiz[i]){
			cout<<0<<endl;
			return 0;
		}else if(esiz[i]==vsiz[i]) MulAs(ans,2);
		else{
			cnt++;
			MulAs(ans,vsiz[i]);
		}
	}
	while(cnt) MulAs(ans,cnt--);

	cout<<ans<<endl;

	return 0;
}