#include<bits/stdc++.h>

using namespace std;

ifstream fin("string.in");
ofstream fout("string.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const ll inf=1e18;

struct Node{
	int son[26],fa,len;
}tr[N<<1];

int cnt,root,lst;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Init(){root=lst=Allc();}
inline void Insert(char c){
	c-='a';
	int p=lst,cur=Allc();
	tr[cur].len=tr[lst].len+1;
	while(p&&!tr[p].son[c]) tr[p].son[c]=cur,p=tr[p].fa;
	int q=tr[p].son[c];
	if(!q) tr[cur].fa=root;
	else if(tr[p].len+1==tr[q].len) tr[cur].fa=q;
	else{
		int r=Clone(q);
		tr[r].len=tr[p].len+1;
		while(p&&tr[p].son[c]==q) tr[p].son[c]=r,p=tr[p].fa;
		tr[cur].fa=tr[q].fa=r;
	}
	lst=cur;
}

string s;
int al[N],ar[N],bl[N],br[N],na,nb,m;
int ap[N],bp[N],pos[N],fa[lgN][N<<1];
vector<int> ext[N<<1],id[N<<1];
inline int GetPos(int l,int r){
	int x=pos[l];
	for(int k=__lg(cnt);~k;k--){
		if(tr[fa[k][x]].len>=r-l+1) x=fa[k][x];
	}
	return x;
}

ll dis[N<<2];
vector<array<int,2>> e[N<<2];
int ind[N<<2],tot;
inline bool Topo(){
	for(int i=1;i<=tot;i++){
		for(auto p:e[i]) ind[p[0]]++;
	}
	queue<int> q;
	for(int i=1;i<=tot;i++) if(!ind[i]) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(auto p:e[x]){
			dis[p[0]]=max(dis[p[0]],dis[x]+p[1]);
			if(!--ind[p[0]]) q.push(p[0]);
		}
	}
	for(int i=1;i<=tot;i++) if(ind[i]) return 0;
	return 1;
}

inline void Solve(){
	cin>>s;
	s=" "+s;
	cin>>na;
	for(int i=1;i<=na;i++) cin>>al[i]>>ar[i];
	cin>>nb;
	for(int i=1;i<=nb;i++) cin>>bl[i]>>br[i];
	
	Init();
	for(int i=s.size()-1;i;i--){
		Insert(s[i]);
		pos[i]=lst;
	}

	for(int i=1;i<=cnt;i++) fa[0][i]=tr[i].fa;
	for(int k=1;k<=__lg(cnt);k++){
		for(int i=1;i<=cnt;i++) fa[k][i]=fa[k-1][fa[k-1][i]];
	}

	for(int i=1;i<=cnt;i++) ext[i].push_back(tr[i].len);
	for(int i=1;i<=na;i++){
		ap[i]=GetPos(al[i],ar[i]);
		ext[ap[i]].push_back(ar[i]-al[i]+1);
	}
	for(int i=1;i<=nb;i++){
		bp[i]=GetPos(bl[i],br[i]);
		ext[bp[i]].push_back(br[i]-bl[i]+1);
	}
	for(int i=1;i<=cnt;i++){
		sort(ext[i].begin(),ext[i].end());
		ext[i].erase(unique(ext[i].begin(),ext[i].end()),ext[i].end());
		id[i].resize(ext[i].size());
		for(int j=0;j<ext[i].size();j++){
			id[i][j]=++tot;
			if(j) e[id[i][j-1]].push_back({id[i][j],0});
		}
	}
	for(int i=1;i<=cnt;i++) if(tr[i].fa) e[id[tr[i].fa].back()].push_back({id[i].front(),0});

	for(int i=1;i<=na;i++){
		int p=lower_bound(ext[ap[i]].begin(),ext[ap[i]].end(),ar[i]-al[i]+1)-ext[ap[i]].begin();
		ap[i]=id[ap[i]][p];
	}
	for(int i=1;i<=nb;i++){
		int p=lower_bound(ext[bp[i]].begin(),ext[bp[i]].end(),br[i]-bl[i]+1)-ext[bp[i]].begin();
		bp[i]=id[bp[i]][p];
	}

	cin>>m;
	while(m--){
		int i,j;
		cin>>i>>j;
		e[ap[i]].push_back({bp[j],ar[i]-al[i]+1});
	}

	if(!Topo()) cout<<-1<<endl;
	else{
		ll ans=0;
		for(int i=1;i<=na;i++) ans=max(ans,dis[ap[i]]+ar[i]-al[i]+1);
		cout<<ans<<endl;
	}

	for(int i=1;i<=cnt;i++){
		memset(&tr[i],0,sizeof tr[i]);
		ext[i].clear();
		id[i].clear();
	}
	for(int i=1;i<=tot;i++){
		dis[i]=ind[i]=0;
		e[i].clear();
	}
	cnt=root=lst=tot=0;
}

signed main(){
	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}