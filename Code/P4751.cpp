#include<bits/stdc++.h>

using namespace std;

<<<<<<< HEAD
#define endl '\n'
const int N=1e6+9;
const int inf=1e9+7;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],n,m,root;

struct Node{
    int lc,rc,fa,hib,lob,f[2][2];
    char op;
}tr[N<<1];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define op(x) tr[x].op
#define fa(x) tr[x].fa
#define hib(x) tr[x].hib
#define lob(x) tr[x].lob
#define f(x,p,q) tr[x].f[p][q] 

int cnt;
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
    if(!lc(x)){
        f(x,0,0)=0;
        f(x,0,1)=a[lob(x)];
        f(x,1,0)=0;
        f(x,1,1)=-inf;
    }else if(op(x)=='C'){ // Compress
        f(x,0,0)=max(-inf,max(f(lc(x),0,1)+f(rc(x),1,0),f(lc(x),0,0)+f(rc(x),0,0)));
        f(x,0,1)=max(-inf,max(f(lc(x),0,1)+f(rc(x),1,1),f(lc(x),0,0)+f(rc(x),0,1)));
        f(x,1,0)=max(-inf,max(f(lc(x),1,1)+f(rc(x),1,0),f(lc(x),1,0)+f(rc(x),0,0)));
        f(x,1,1)=max(-inf,max(f(lc(x),1,1)+f(rc(x),1,1),f(lc(x),1,0)+f(rc(x),0,1)));
    }else{ // Rake
        f(x,0,0)=max(-inf,max(f(lc(x),0,0)+f(rc(x),0,0),f(lc(x),0,0)+f(rc(x),0,1)));
        f(x,0,1)=max(-inf,max(f(lc(x),0,1)+f(rc(x),0,0),f(lc(x),0,1)+f(rc(x),0,1)));
        f(x,1,0)=max(-inf,max(f(lc(x),1,0)+f(rc(x),1,0),f(lc(x),1,0)+f(rc(x),1,1)));
        f(x,1,1)=max(-inf,max(f(lc(x),1,1)+f(rc(x),1,0),f(lc(x),1,1)+f(rc(x),1,1)));
    }
}

int siz[N],fa[N],hson[N];
inline void DFS(int x){
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[hson[x]]) hson[x]=y;
    }
}
inline int Divide(int l,int r,char op,vector<int> &node,vector<int> &sum){
    if(l==r) return node[l];
    int w=sum[r]-(l?sum[l-1]:0);
    int lp=l,rp=r+1;
    while(lp+1<rp){
        int mid=lp+rp>>1;
        if(sum[mid]-(l?sum[l-1]:0)<=w/2) lp=mid;
        else rp=mid;
    }
    int x=Allc();
    op(x)=op;
    hib(x)=hib(node[l]);
    lob(x)=op=='R'?lob(node[l]):lob(node[r]);
    lc(x)=Divide(l,lp,op,node,sum);
    rc(x)=Divide(lp+1,r,op,node,sum);
    fa(lc(x))=fa(rc(x))=x;
    PushUp(x);
    return x;
}
int id[N];
inline void Build(int x,bool flag=true){
    id[x]=x,op(x)='N';
    hib(id[x])=fa[x],lob(id[x])=x;
    PushUp(id[x]);

    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        Build(y,true);
    }
    
    if(!hson[x]) return ;
    vector<int> node,sum;
    Build(hson[x],false);
    node.push_back(id[hson[x]]);
    sum.push_back(1);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(y==hson[x]) continue ;
        node.push_back(id[y]);
        sum.push_back(siz[y]);
    }
    for(int i=1;i<sum.size();i++) sum[i]+=sum[i-1];
    id[hson[x]]=Divide(0,node.size()-1,'R',node,sum);

    if(!flag) return ;
    node.clear();
    sum.clear();
    for(int y=x;y;y=hson[y]){
        node.push_back(id[y]);
        sum.push_back(siz[y]-siz[hson[y]]);
    }
    for(int i=1;i<sum.size();i++) sum[i]+=sum[i-1];
    id[x]=Divide(0,node.size()-1,'C',node,sum);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AddEdge(u,v);
        AddEdge(v,u);
    }
    AddEdge(n+1,1);
    AddEdge(1,n+1);

    cnt=n;
    root=1;
    DFS(n+1);
    Build(1,true);
    
    int ans=0;
    while(m--){
        int x,k;
        cin>>x>>k;
        x^=ans;
        a[x]=k;
        int cur=x;
        while(cur){
            PushUp(cur);
            cur=fa(cur);
        }
        ans=max(max(f(id[1],0,0),f(id[1],0,1)),max(f(id[1],1,0),f(id[1],1,1)));
        cout<<ans<<endl;
    }

    return 0;
=======
using ll=long long;
const int N=1e6+9;
const ll lnf=1e18;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],siz[N],hson[N],w[N],n;
inline void DFS(int x){
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		DFS(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}

struct Node{
	int lc,rc,fa;
	int hib,lob;
	ll f[2][2];
	char op;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define fa(x) tr[x].fa
#define hib(x) tr[x].hib
#define lob(x) tr[x].lob
#define f(x,i,j) tr[x].f[i][j]
#define op(x) tr[x].op

inline void PushUp(int x){
	if(op(x)=='N'){
		f(x,0,0)=0;
		f(x,0,1)=w[lob(x)];
		f(x,1,0)=w[hib(x)];
		f(x,1,1)=-lnf;
	}else if(op(x)=='C'){
		f(x,0,0)=max(f(lc(x),0,0)+f(rc(x),0,0),f(lc(x),0,1)+f(rc(x),1,0)-w[lob(lc(x))]);
		f(x,0,1)=max(f(lc(x),0,0)+f(rc(x),0,1),f(lc(x),0,1)+f(rc(x),1,1)-w[lob(lc(x))]);
		f(x,1,0)=max(f(lc(x),1,0)+f(rc(x),0,0),f(lc(x),1,1)+f(rc(x),1,0)-w[lob(lc(x))]);
		f(x,1,1)=max(f(lc(x),1,0)+f(rc(x),0,1),f(lc(x),1,1)+f(rc(x),1,1)-w[lob(lc(x))]);
	}else{
		f(x,0,0)=f(lc(x),0,0)+max(f(rc(x),0,0),f(rc(x),0,1));
		f(x,0,1)=f(lc(x),0,1)+max(f(rc(x),0,0),f(rc(x),0,1));
		f(x,1,0)=f(lc(x),1,0)+max(f(rc(x),1,0),f(rc(x),1,1))-w[hib(lc(x))];
		f(x,1,1)=f(lc(x),1,1)+max(f(rc(x),1,0),f(rc(x),1,1))-w[hib(lc(x))];
	}
}

int fa[N],siz[N],hson[N];
inline void DFS(int x){

}

int id[N];
inline void Build(int x){

}

signed main(){
	return 0;
>>>>>>> d8147174aa15e80698100c4d67760eaf3e5689db
}