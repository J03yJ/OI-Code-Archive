#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

vector<int> fa;
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		vector<int> u(m),v(m);
		for(int i=0;i<m;i++) cin>>u[i]>>v[i];

		vector<vector<int>> seg(n+1);
		for(int i=0;i<m;i++) seg[v[i]].push_back(i);

		vector<int> t(n+1,0),nxt(n+1,0);
		t[0]=-1;
		for(int i=1;i<=n;i++) nxt[i]=i;
		for(int i=1;i<=n;i++){
			t[i]=n+1;
			sort(seg[i].begin(),seg[i].end(),[&](int i,int j){return u[i]<u[j];});
			for(int j:seg[i]){
				t[i]=min(t[i],t[u[j]]+1);
				nxt[u[j]+1]=max(nxt[u[j]+1],i-t[i]);
			}
			t[i]=min(t[i],t[i-1]+1);
		}
		
		fa=vector<int>(n+1);
		iota(fa.begin(),fa.end(),0);
		for(int i=1;i<=n;i++){
			for(int j=Find(i);j<nxt[i];j=Find(j)){
				Merge(j+1,j);
			}
		}

		for(int i=1;i<n;i++) cout<<(i==Find(i));cout<<endl;
	}

	return 0;
}