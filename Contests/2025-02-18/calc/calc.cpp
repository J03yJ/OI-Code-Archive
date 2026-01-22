#include<bits/stdc++.h>

using namespace std;

ifstream fin("calc.in");
ofstream fout("calc.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int c[N],n,m,q;

namespace Brute{
    const int N=5e3+9;
    int tmp[N];
    inline void Clear(){for(int i=1;i<=m;i++) tmp[i]=0;}
    inline void Calc(int x,int fa,int dis){
        tmp[c[x]]=max(tmp[c[x]],dis);
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa) continue ;
            Calc(y,x,dis+w[i]);
        }
    }
    inline int F(int x){
        int sum=0;
        Clear(),Calc(x,0,0);
        for(int i=1;i<=m;i++) sum+=tmp[i];
        return sum;
    }
    inline ll Sum(int x,int fa,int u,int flag){
        ll res=0;
        if(x==u) flag=1;
        if(flag) res+=F(x);
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa) continue ;
            res+=Sum(y,x,u,flag);
        }
        return res;
    }
    inline void Solve(){
        while(q--){
            int op;
            cin>>op;
            if(op==1){
                int u,x;
                cin>>u>>x;
                c[u]=x;
            }else{
                int u;
                cin>>u;
                cout<<Sum(1,0,u,0)<<endl;
            }
        }
    }
}

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        AddEdge(u,v,w),AddEdge(v,u,w);
    }

    Brute::Solve();

    return 0;
}