#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);i++)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class T1,class T2>void ChMin(T1 &x,T2 y){if(y<x) x=y;}
template<class T1,class T2>void ChMax(T1 &x,T2 y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

const int N=2e5+9;
const int inf=1e9;

#define int ll
#define Clp(x,l,r) max(min(x,r),l)
int al[N],ar[N],fa[N],n;
vector<int> e[N];
ll cur[N],op[N],dlt;
void DFS1(int x,int k){
    cur[x]=Clp(k,al[x],ar[x]);
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS1(y,k);
        op[y]+=cur[x]-cur[y];
        dlt+=max(-op[y],0ll);
    }
}
void DFS2(int x,ll tag){
    tag+=op[x];
    cur[x]+=tag;
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        DFS2(y,tag);
    }
}
int Solve(int k){
    dlt=0;
    For(i,1,n) cur[i]=op[i]=0;
    DFS1(1,k);
    DFS2(1,0);
    For(i,1,n) cur[i]+=dlt;
    return cur[1];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        For(i,1,n) cin>>al[i]>>ar[i];
        For(i,1,n-1){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        int l=0,r=inf;
        while(l+1<r){
            int tmp=(r-l+1)/3;
            int p1=l+tmp,p2=r-tmp;
            ll x=Solve(p1),y=Solve(p2);
            if(x>y) l=p1;
            else r=p2;
        }
        cout<<min(Solve(l),Solve(r))<<endl;

        For(i,1,n) e[i].clear();
    }

    return 0;
}