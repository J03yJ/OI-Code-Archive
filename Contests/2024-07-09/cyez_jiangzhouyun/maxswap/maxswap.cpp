#include<bits/stdc++.h>

using namespace std;

ifstream fin("maxswap.in");
ofstream fout("maxswap.out");
#define cin fin
#define cout fout

#define int long long
const int N=5e5+9;
const int inf=1e9;

int fi[N],ne[N],to[N],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

struct node{
    int lc,rc,dat,tag;
    node(){tag=0;}
    node(int l,int r,int val){
        lc=l;rc=r;dat=val;
        tag=0;
    }
};
node mem[N<<1];int cnt;
struct meap{
    int root;
    meap(){root=0;}
    meap(int x){mem[++cnt]=node(0,0,x);root=cnt;}

    void pushdown(int x){
        if(mem[x].lc) mem[mem[x].lc].dat+=mem[x].tag,mem[mem[x].lc].tag+=mem[x].tag;
        if(mem[x].rc) mem[mem[x].rc].dat+=mem[x].tag,mem[mem[x].rc].tag+=mem[x].tag;
        mem[x].tag=0;
    }
    int merge(int x,int y){
        if(!x||!y) return x|y;
        if(mem[x].dat<mem[y].dat) swap(x,y);
        pushdown(x);
        pushdown(y);
        mem[x].lc=merge(mem[x].lc,y);
        return x;
    }
    void tag(int val){
        mem[root].dat+=val;
        mem[root].tag+=val;
    }

    void operator +=(meap x){root=merge(root,x.root);}
    int top(){
        return mem[root].dat;
    }
    void pop(){
        pushdown(root);
        root=merge(mem[root].lc,mem[root].rc);
    }
    bool empty(){
        return !root;
    }
};

int dep[N],a[N],ans,C;
meap h[N];
void dfs(int x){
    if(a[x]) h[x]=meap(0);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        dfs(y);
        h[y].tag(1);
        h[x]+=h[y];
    }
    if(!a[x]){
        if(h[x].empty()) return ;
        // cout<<x<<'/'<<ans<<" : "<<C<<' '<<ans+C<<endl;
        // h[x].debug(h[x].root);
        // cout<<endl;
        ans+=h[x].top();
        h[x].pop();
        h[x]+=meap(0);
        // cout<<x<<' ';
        // h[x].debug(h[x].root);
        // cout<<endl;
    }else C++;
}

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='1') a[i]=1;
    }
    for(int i=1,u,v;i<n;i++) cin>>u>>v,adeg(v,u);

    dfs(1);
    cout<<ans<<endl;

    return 0;
}