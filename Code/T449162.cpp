#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int N=1e5+9;

int a[N],b[N],l[N],r[N];

int fi[N],ne[N<<1],to[N<<1],adj;
void AddEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int dfn[N],idf[N],siz[N],dcnt;
void DFS(int x){
    dfn[x]=++dcnt;
    idf[dcnt]=x;
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(dfn[y]) continue ;
        DFS(y);
        siz[x]+=siz[y];
    }
}

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        AddEg(x,y);
        AddEg(y,x);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    DFS(1);

    vector<int> stk;
    for(int i=1;i<=n;i++){
        if(a[idf[i]]%k) continue ;
        while(stk.size()&&a[idf[stk.back()]]<=a[idf[i]]){
            r[idf[stk.back()]]=i-1;
            stk.pop_back();
        }
        if(stk.size()) l[idf[i]]=stk.front()+1;
        else l[idf[i]]=1;
        stk.push_back(i);
    }
    while(stk.size()){
        r[idf[stk.back()]]=n;
        stk.pop_back();
    }
    for(int i=1;i<=n;i++) cout<<idf[i]<<' ';cout<<endl;
    for(int i=1;i<=n;i++) cout<<l[i]<<' '<<r[i]<<endl;

    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=dfn[i];j<=dfn[i]+siz[i]-1;j++){
            if(a[idf[j]]%k) continue ;
            int L=max(dfn[i],l[idf[j]]),R=min(dfn[i]+siz[i]-1,r[idf[j]]);
            cout<<L<<' '<<R<<' '<<idf[j]<<' '<<b[a[idf[j]]]<<endl;
            ans=(ans+QPow(2,R-L)*b[a[idf[j]]]%mod)%mod;
        }
        cout<<ans<<endl;
    }

    return 0;
}