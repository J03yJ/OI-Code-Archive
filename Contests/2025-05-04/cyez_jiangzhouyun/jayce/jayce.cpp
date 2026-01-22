#include<bits/stdc++.h>

using namespace std;

ifstream fin("jayce.in");
ofstream fout("jayce.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e2+9;

int f[N],vis[N],dis[N],dep[N],r[N],n;
vector<int> son[N];

signed main(){
    int Tid,T;
    cin>>Tid>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>f[i];

        ll res=1;
        for(int i=1;i<=n;i++){
            if(vis[i]) continue ;
            int x=i,len=0;
            while(!vis[x]){
                dis[x]=len++;
                vis[x]=i;
                x=f[x];
            }
            if(vis[x]!=i) continue ;
            ll k=len-dis[x];
            res=res/__gcd(res,k)*k;
            int y=x;
            do{
                r[y]=1;
                y=f[y];
            }while(y!=x);
        }

        int maxdep=0;
        for(int i=1;i<=n;i++) if(!r[i]) son[f[i]].push_back(i);
        queue<int> q;
        for(int i=1;i<=n;i++) if(r[i]) q.push(i);
        while(q.size()){
            int x=q.front();
            q.pop();
            for(int y:son[x]){
                dep[y]=dep[x]+1;
                maxdep=max(maxdep,dep[y]);
                q.push(y);
            }
        }

        ll ans=res;
        while(ans<maxdep) ans+=res;
        cout<<ans<<endl;

        for(int i=1;i<=n;i++){
            son[i].clear();
            r[i]=vis[i]=dep[i]=dis[i]=0;
        }
    }

    return 0;
}