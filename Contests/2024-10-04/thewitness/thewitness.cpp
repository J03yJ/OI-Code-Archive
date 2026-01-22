#include<bits/stdc++.h>

using namespace std;

ifstream fin("thewitness.in");
ofstream fout("thewitness.out");
#define cin fin
#define cout fout

#define int long long
#define Mask(k) ((1<<k)-1)
#define Allc(x) x.begin(),x.end()
const int mod=998244353;

signed main(){
    int n,m;
    cin>>n>>m;    
    if(n<m) swap(n,m);

    if(n%2&&m%2){
        cout<<0<<endl;
        return 0;
    }

    vector<int> f(1<<m,0),g(1<<m,0);
    vector<vector<int>> nxt(1<<m,vector<int>());
    for(int sta=Mask(m);~sta;sta--){
        nxt[sta].push_back(sta);
        for(int i=0;i<m-1;i++){
            if(!(sta>>i&3)) for(int x:nxt[sta|(3<<i)]) nxt[sta].push_back(x);
        }
        sort(Allc(nxt[sta]));
        int cnt=unique(Allc(nxt[sta]))-nxt[sta].begin();
        while(nxt[sta].size()>cnt) nxt[sta].pop_back();
    }

    g[Mask(m)]=1;
    for(int i=1;i<=n;i++){
        swap(f,g);
        g=vector<int>(1<<m,0);
        for(int sta=0;sta<(1<<m);sta++){
            for(int tta:nxt[sta^Mask(m)]) g[tta]=(g[tta]+f[sta])%mod;
        }
    }
    cout<<g[Mask(m)]<<endl;

    return 0;
}