#include<bits/stdc++.h>

using namespace std;

ifstream fin("majik.in");
ofstream fout("majik.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e4+9;
const int inf=1e9+7;

bitset<N> w[N];
int l[N],r[N],n,s,t;

int lev[N],cur[N];
inline bool BFS(){
	for(int i=1;i<=t;i++) lev[i]=0,cur[i]=1;
	lev[s]=1;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t) return 1;
		for(int y=1;y<=t;y=w[x]._Find_next(y)){
			if(!w[x][y]) continue ;
			if(lev[y]) continue ;
			lev[y]=lev[x]+1;
			q.push(y);
		}
	}
	return 0;
}
inline int DFS(int x,int lft){
	if(x==t) return lft;
	int k=lft;
	for(int &y=cur[x];y<=t;y=w[x]._Find_next(y)){
		if(!w[x][y]) continue ;
		if(lev[y]!=lev[x]+1) continue ;
		int tmp=DFS(y,min(lft,int(w[x][y])));
		k-=tmp,w[x].set(y,w[x][y]^tmp),w[y].set(x,w[y][x]^tmp);
		if(!k) return lft;
	}
	return lft-k;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
	}

	s=(n<<1)+1,t=(n<<1)+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue ;
			if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]){
				w[l[j]][r[i]]=1;
			}
		}
	}
	for(int i=1;i<=n;i++) w[s][l[i]]=w[r[i]][t]=1;

	int sum=0,cnt=0;
	while(BFS()) sum+=DFS(s,inf),cnt++;

	cout<<(n<<1)-sum<<endl;

	return 0;
}