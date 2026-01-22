#include<bits/stdc++.h>

using namespace std;

ifstream fin("catch.in");
ofstream fout("catch.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e6+9;

int lc[N],rc[N],f[N][22],dep[N],p[N],n;
inline void DFS1(int x){
    if(!lc[x]&&!rc[x]){
        dep[x]=1,p[x]=x;
        return ;
    }
    p[x]=1e8,dep[x]=1e8;
    if(lc[x]) DFS1(lc[x]),dep[x]=min(dep[x],dep[lc[x]]+1);
    if(rc[x]) DFS1(rc[x]),dep[x]=min(dep[x],dep[rc[x]]+1);
    if(lc[x]&&dep[lc[x]]+1==dep[x]) p[x]=min(p[x],p[lc[x]]);
    if(rc[x]&&dep[rc[x]]+1==dep[x]) p[x]=min(p[x],p[rc[x]]);
}
inline void DFS2(int x){
    if(!x) return ;
    f[x][21]=1e8;
    if(dep[x]<=20) f[p[x]][dep[x]]++;
    if(!lc[x]&&!rc[x]){
        for(int i=1;i<=20;i++) f[x][i]+=f[x][i-1];
        return ;
    }
    DFS2(lc[x]),DFS2(rc[x]);
    for(int i=0;i<=20;i++) f[x][i]=min(f[lc[x]][i]+f[rc[x]][i+1],f[lc[x]][i+1]+f[rc[x]][i]);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>lc[i]>>rc[i];

    DFS1(1);
    DFS2(1);
    cout<<f[1][0]<<endl;

    return 0;
}