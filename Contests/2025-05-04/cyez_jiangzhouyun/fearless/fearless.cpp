#include<bits/stdc++.h>

using namespace std;

ifstream fin("fearless.in");
ofstream fout("fearless.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=(1<<21)+9;
const int inf=1e9;

mt19937 rng(4649);
int a[N],b[N],c[N],buc[N],col[N],fa[N],n,m;
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
vector<int> e[N];
inline void Work(vector<int> &p,int d,int id){
    if(!p.size()) return ;
    if(!~d){
        c[p.back()]=id;
        return ;
    }

    vector<int> l,r;
    for(int i:p) fa[i]=i;

    for(int i:p) buc[a[i]]=i;
    for(int i:p){
        int j=buc[a[i]^(1<<d)];
        if(!j) continue ;
        e[i].push_back(j);
        Merge(i,j);
    }
    for(int i:p) buc[a[i]]=0;
    for(int i:p) buc[b[i]]=i;
    for(int i:p){
        int j=buc[b[i]^(1<<d)];
        if(!j) continue ;
        e[i].push_back(j);
        Merge(i,j);
    }
    for(int i:p) buc[b[i]]=0;

    queue<int> q;
    for(int i:p){
        if(fa[i]==i) col[i]=1,q.push(i);
        else col[i]=0;
    }
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int y:e[x]){
            if(col[y]) continue ;
            col[y]=-col[x];
            q.push(y);
        }
    }
    for(int i:p){
        if(col[i]==1) l.push_back(i);
        else r.push_back(i);
    }
    for(int i:p){
        e[i].clear();
        col[i]=0;
    }

    for(int i:p) a[i]^=(a[i]>>d&1)<<d;
    for(int i:p) b[i]^=(b[i]>>d&1)<<d;
    Work(l,d-1,id<<1);
    Work(r,d-1,id<<1|1);
}
inline void Solve(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i];

    map<int,int> amp,bmp;
    for(int i=1;i<=m;i++) amp[a[i]]++,bmp[b[i]]++;
    for(auto p:amp){
        if(p.second>1){
            cout<<"NO"<<endl;
            return ;
        }
    }
    for(auto p:bmp){
        if(p.second>1){
            cout<<"NO"<<endl;
            return ;
        }
    }

    vector<int> p(m);
    iota(p.begin(),p.end(),1);
    Work(p,n-1,0);

    cout<<"YES"<<endl;
    for(int i=1;i<=m;i++) cout<<c[i]<<' ';cout<<endl;
}

signed main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}