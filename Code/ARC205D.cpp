#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

int fa[N],siz[N],n;
vector<int> e[N];

inline int Solve(int x,int lft){
	if(!e[x].size()) return 0;
	sort(e[x].begin(),e[x].end(),[](int i,int j){return siz[i]>siz[j];});
	lft=max(lft-1,0);
	int y=e[x].front();
	if(siz[y]-lft>siz[x]-siz[y]-1){
		int tmp=siz[x]-siz[y]-1;
		return tmp+Solve(y,tmp+lft);
	}else return (siz[x]-lft-1)/2;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=2;i<=n;i++) cin>>fa[i],e[fa[i]].push_back(i);
		
		for(int i=1;i<=n;i++) siz[i]=1;
		for(int i=n;i>=1;i--) siz[fa[i]]+=siz[i];

		cout<<Solve(1,0)<<endl;
		
		for(int i=1;i<=n;i++){
			fa[i]=siz[i]=0;
			e[i].clear();
		}
	}

	return 0;
}