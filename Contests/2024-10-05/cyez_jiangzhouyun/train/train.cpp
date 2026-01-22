#include<bits/stdc++.h>

using namespace std;

ifstream fin("train.in");
ofstream fout("train.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],siz[N],n,ans;
void DFS(int x){
    int mx=0;
    vector<int> v;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        DFS(y);
        siz[x]+=siz[y];
        mx=max(mx,siz[y]);
    }
    if(mx>siz[x]/2) ans+=mx*(siz[x]-mx);
    else{
        
    }

    siz[x]++;
}

signed main(){
    cin>>n;
    for(int i=2;i<=n;i++) cin>>fa[i],AdEg(fa[i],i);

    DFS(1);
    cout<<ans<<endl;

    return 0;
}