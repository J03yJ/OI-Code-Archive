#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6e5+9;

int s[N],t[N],aval[N],bval[N],aid[N],bid[N],n,tot;
vector<int> e[N<<4];
int d[N<<4],id[N<<4],icnt;
inline void CountD(){
	for(int i=1;i<=tot;i++){
		for(int j:e[i]) d[j]++;
	}
}
inline void Topo(){
	queue<int> q;
	for(int i=1;i<=tot;i++) if(!d[i]) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		id[x]=++icnt;
		for(int y:e[x]){
			d[y]--;
			if(!d[y]) q.push(y);
		}
	}
}
inline bool Check(){
	for(int i=1;i<=n+n;i++) if(d[i]) return 0;
	return 1;
}

struct Seg{
	int lc[N<<3],rc[N<<3];
	inline int Build(int l,int r,int flag){
		int x=++tot;
		if(l==r){
			if(!flag) e[x].push_back(bid[l])/* ,cout<<x<<" -> "<<bid[l]<<endl */;
			else e[aid[l]].push_back(x)/* ,cout<<aid[l]<<" -> "<<x<<endl */;
			return x;
		}
		int mid=l+r>>1;
		lc[x]=Build(l,mid,flag);
		rc[x]=Build(mid+1,r,flag);
		// cout<<x<<" : "<<l<<' '<<r<<' '<<flag<<endl;
		if(!flag) e[x].push_back(lc[x]),e[x].push_back(rc[x])/* ,cout<<x<<" -> "<<lc[x]<<" , "<<rc[x]<<endl */;
		else e[lc[x]].push_back(x),e[rc[x]].push_back(x)/* ,cout<<lc[x]<<" , "<<rc[x]<<" -> "<<x<<endl */;
		return x;
	}
	inline void Link(int x,int L,int R,int l,int r,int flag,int u){
		// cerr<<x<<" : "<<L<<' '<<R<<' '<<l<<' '<<r<<endl;
		if(l<=L&&R<=r){
			if(!flag) e[u].push_back(x)/* ,cout<<u<<" -|> "<<x<<endl */;
			else e[x].push_back(u)/* ,cout<<x<<" -|> "<<u<<endl */;
			return ;
		}
		int mid=L+R>>1;
		if(l<=mid) Link(lc[x],L,mid,l,r,flag,u);
		if(r>mid) Link(rc[x],mid+1,R,l,r,flag,u);
	}
}at,bt;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]>>t[i];

	tot=n*2;
	for(int i=1;i<=n;i++) e[i].push_back(i+n);
	for(int i=1;i<=n;i++) aval[i]=s[i],bval[i]=t[i];
	sort(aval+1,aval+n+1),sort(bval+1,bval+n+1);
	for(int i=1;i<=n;i++){
		int apos=lower_bound(aval+1,aval+n+1,s[i])-aval;
		int bpos=lower_bound(bval+1,bval+n+1,t[i])-bval;
		aid[apos]=i+n;
		bid[bpos]=i;
	}
	// for(int i=1;i<=n;i++) cout<<aid[i]<<' ';cout<<endl;
	// for(int i=1;i<=n;i++) cout<<bid[i]<<' ';cout<<endl;
	int art=at.Build(1,n,1);
	int brt=bt.Build(1,n,0);
	// cout<<art<<' '<<brt<<endl;
	for(int i=1;i<=n;i++){
		int l=min(s[i],t[i])+1,r=max(s[i],t[i])-1;
		int al=lower_bound(aval+1,aval+n+1,l)-aval;
		int ar=upper_bound(aval+1,aval+n+1,r)-aval-1;
		if(al<=ar) at.Link(art,1,n,al,ar,1,i);
		int bl=lower_bound(bval+1,bval+n+1,l)-bval;
		int br=upper_bound(bval+1,bval+n+1,r)-bval-1;
		if(bl<=br) bt.Link(brt,1,n,bl,br,0,i+n);
		// cout<<i<<" : "<<l<<' '<<r<<' '<<al<<' '<<ar<<' '<<bl<<' '<<br<<endl;
	}

	CountD();
	Topo();
	
	if(!Check()) cout<<"No"<<endl;
	else{
		cout<<"Yes"<<endl;
		vector<int> p(n);
		iota(p.begin(),p.end(),1);
		sort(p.begin(),p.end(),[](int i,int j){return id[i]<id[j];});
		for(int i:p) cout<<i<<' ';cout<<endl;
	}

	return 0;
}