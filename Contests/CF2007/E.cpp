#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;

int fa[N],u[N],w[N],t[N],c[N],n,k;
int l[N],r[N];
vector<int> son[N];
void ClearE(){
    for(int i=1;i<=n;i++) son[i].clear();
}
void DFS(int x){
    l[x]=r[x]=x;
    for(int y:son[x]){
        DFS(y);
        r[x]=max(r[x],r[y]);
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=2;i<=n;i++) cin>>fa[i],son[fa[i]].push_back(i);
        for(int i=1;i<n;i++) cin>>u[i]>>w[i];
        
        DFS(1);
        for(int i=1;i<n;i++) t[l[u[i]]]=t[r[u[i]]%n+1]=i;
        for(int i=1;i<=n;i++) c[1]++,c[t[i]]--;
        for(int i=1;i<n;i++) c[i]+=c[i-1];
        // for(int i=1;i<=n;i++) cout<<t[i]<<' ';cout<<endl;
        // for(int i=1;i<n;i++) cout<<c[i]<<' ';cout<<endl;

        for(int i=1,ans=0;i<n;i++){
            k-=w[i];
            ans+=2*w[i];
            cout<<ans+c[i]*k<<' ';
        }
        cout<<endl;

        for(int i=1;i<=n;i++) c[i]=0;
        ClearE();
    }
}