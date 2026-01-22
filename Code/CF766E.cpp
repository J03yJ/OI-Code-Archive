#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],p[N],n,ans;
vector<vector<int>> DFS(int x,int fa){
    vector<vector<int>> cx(21,{0,0});
    p[x]=p[fa]^a[x];
    for(int k=0;k<20;k++) cx[k][p[x]>>k&1]++;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        auto cy=DFS(y,x);
        for(int k=0;k<20;k++){
            if(a[x]>>k&1){
                ans+=cx[k][0]*cy[k][0]*(1<<k);
                ans+=cx[k][1]*cy[k][1]*(1<<k);
            }else{
                ans+=cx[k][0]*cy[k][1]*(1<<k);
                ans+=cx[k][1]*cy[k][0]*(1<<k);
            }
        }
        for(int k=0;k<20;k++) cx[k][0]+=cy[k][0];
        for(int k=0;k<20;k++) cx[k][1]+=cy[k][1];
    }
    ans+=a[x];
    return cx;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    DFS(1,0);

    cout<<ans<<endl;

    return 0;
}