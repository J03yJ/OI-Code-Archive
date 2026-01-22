#include<bits/stdc++.h>

using namespace std;

ifstream fin("dsu.in");
ofstream fout("dsu.out");
#define cin fin
#define cout fout
#define endl '\n'

#define fir(x) (x).first
#define sec(x) (x).second
using pdi=pair<double,int>;
const int N=2e3+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],a[N],n;
inline void DFS(int x){
    a[x]=-1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS(y);
        a[x]++;
    }
}

int top[N];
inline int Find(int x){return top[x]==x?x:top[x]=Find(top[x]);}
inline void Merge(int x,int y){top[Find(y)]=Find(x);}
int hd[N],tl[N],nxt[N],len[N],sum[N];
template<class T> struct DelHeap{
    priority_queue<T> p,q;
    inline void Push(T x){p.push(x);}
    inline void Pop(T x){q.push(x);}
    inline T Top(){
        while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline int Size(){return p.size()-q.size();}
};

signed main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        u++,v++;
        AddEdge(u,v);
        AddEdge(v,u);
    }

    int ans=0;
    for(int root=1;root<=n;root++){
        fa[root]=0,DFS(root);
        a[root]++;  
        DelHeap<tuple<double,int,int>> q;
        for(int i=1;i<=n;i++){
            nxt[i]=0;
            len[i]=1,top[i]=i;
            hd[i]=tl[i]=i;
            sum[i]=a[i];
            q.Push(make_tuple(double(sum[i])/len[i],len[i],i));
        }
        while(q.Size()){
            int x=get<2>(q.Top()),l=get<1>(q.Top());
            q.Pop(q.Top());
            if(l!=len[x]) continue ;
            if(!fa[x]) continue ;
            int y=Find(fa[x]);
            Merge(y,x);
            nxt[tl[y]]=hd[x];
            tl[y]=tl[x];
            sum[y]+=sum[x];
            len[y]+=len[x];
            q.Push(make_tuple(double(sum[y])/len[y],len[y],y));
        }
        int x=hd[root],res=n-1,cnt=0;
        while(x){
            cnt++;
            res+=a[x]*(n-cnt+1);
            x=nxt[x];
        }
        ans=max(ans,res);
    }
    cout<<ans<<endl;
    
    return 0;
}