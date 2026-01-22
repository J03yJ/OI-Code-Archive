#include<bits/stdc++.h>

using namespace std;

ifstream fin("convert.in");
ofstream fout("convert.out");
#define cin fin
#define cout fout

const int N=1e3+9;

set<int> e[N];
inline void Insert(int u,int v){
    e[u].insert(v);
    e[v].insert(u);
}
inline void Erase(int u,int v){
    e[u].erase(v);
    e[v].erase(u);
}

void Find(int x,int fa,int p,int &q){
    for(int y:e[x]){
        if(y==fa) continue ;
        if(y==p) return q=x,void();
        Find(y,x,p,q);
        if(q) return ;
    }
}

int n,m;

signed main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        Insert(u,v);
    }

    cout<<"YES"<<endl;
    cout<<m<<endl;
    while(m--){
        int p,q,r=0;
        cin>>p>>q;
        Find(p,-1,q,r);
        cout<<q<<' '<<r<<' '<<p<<' '<<q<<endl;
        Erase(q,r);
        Insert(p,q);
    }

    return 0;
}