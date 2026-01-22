#include<bits/stdc++.h>

using namespace std;

ifstream fin("flow.in");
ofstream fout("flow.out");
#define cin fin
#define cout fout

using ll=long long;
const int N=5e3+9;

int n;
ll s[N],t[N];
vector<int> e[N];

inline ll Work(int x,int fa){
    ll sum=min(s[x],t[x]);
    s[fa]+=sum,s[x]-=sum;
    for(int y:e[x]) if(y!=fa) sum+=Work(y,x);
    return sum;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(int i=2;i<=n;i++) cin>>s[i];
        for(int i=2;i<=n;i++) cin>>t[i];

        ll ans=0;
        while(Work(1,0)) ans++;
        cout<<ans<<endl;

        for(int i=1;i<=n;i++) e[i].clear();
    }

    return 0;
}