#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.out");
#define cin fin
#define cout fout

#define ll long long
const int N=2e5+9;

int a[N],b[N],p[N],val[N],n,m,c,T;
vector<pair<int,int>> e[N<<3];

const ll inf=1e18;
ll dis[N<<3],vis[N<<3];
void Dij(int s){
    priority_queue<pair<int,int>> q;
    for(int i=1;i<=n*5;i++) dis[i]=inf,vis[i]=0;
    dis[s]=0;
    q.push({0,s});
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue ;
        vis[x]=1;
        // cout<<x<<" : "<<dis[x]<<endl;
        for(auto p:e[x]){
            // cout<<x<<'/'<<p.first<<" : "<<dis[x]+p.second<<' '<<dis[p.first]<<endl;
            if(dis[x]+p.second<dis[p.first]){
                dis[p.first]=dis[x]+p.second;
                q.push({-dis[p.first],p.first});
            }
        }
    }
}

int main(){
    cin>>c>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        iota(p+1,p+n+1,1);
        sort(p+1,p+n+1,[](int x,int y){return b[x]<b[y];});
        for(int i=1;i<=n;i++) val[i]=b[p[i]];

        for(int i=1;i<=n;i++) e[i+n].push_back({p[i],0});
        for(int i=1;i<n;i++) e[i+n].push_back({i+1+n,b[p[i+1]]-b[p[i]]});
        for(int i=1;i<=n;i++) e[i+n+n].push_back({p[i],b[p[i]]});
        for(int i=n;i>=2;i--) e[i+n+n].push_back({i-1+n+n,0});

        for(int i=1;i<=n;i++){
            int pos=lower_bound(val+1,val+n+1,m-a[i])-val;
            // cout<<i<<" : "<<pos<<' '<<pos-1+n+n<<' '<<pos+n<<endl;
            if(pos>1) e[i].push_back({pos-1+n+n,a[i]});
            if(pos<=n) e[i].push_back({pos+n,a[i]+b[p[pos]]-m});
        }
        Dij(1);
        cout<<dis[n]<<endl;

        for(int i=1;i<=n*3;i++) e[i].clear();
    }

    return 0;
}