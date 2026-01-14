#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.ans");
#define cin fin
#define cout fout

#define ll long long
const int N=2e5+9;

int a[N],b[N],n,m,c,T;

const ll inf=1e18;
ll dis[N],vis[N];
void Prim(int s){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    dis[s]=0;
    for(int t=1;t<=n;t++){
        int pos=0;
        for(int i=1;i<=n;i++) if(!vis[i]) if(!pos||dis[i]<dis[pos]) pos=i;
        cout<<pos<<' '<<dis[pos]<<endl;
        if(!pos) return ;
        vis[pos]=1;
        for(int i=1;i<=n;i++) dis[i]=min(dis[i],dis[pos]+(a[pos]+b[i])%m);
    }
}

int main(){
    cin>>c>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        
        Prim(1);
        cout<<dis[n]<<endl;
    }

    return 0;
}