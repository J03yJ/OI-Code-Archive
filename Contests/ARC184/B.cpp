#include<bits/stdc++.h>

using namespace std;

#define int long long
int f[1<<20],g[1<<20];
#define Mask(x) ((1<<x)-1)
int Solve(int n){
    vector<int> c;
    for(int x=1;x<=n;x<<=1){
        int cnt=0;
        for(int y=x;y<=n;y*=3) cnt++;
        c.push_back(cnt);
    }

    if(c.size()==1) return c[0]+1>>1;

    memset(f,0x3f,sizeof(int)<<c[0]);
    for(int sta=0;sta<(1<<c[0]);sta++){
        if(((sta|sta<<1)&Mask(c[0]))==Mask(c[0])){
            f[sta&Mask(c[1])]=min(f[sta&Mask(c[1])],0ll+__builtin_popcount(sta));
        }
    }
    for(int i=1;i<c.size();i++){
        int suc=(i==c.size()-1)?0:c[i+1];
        memcpy(g,f,sizeof(int)<<c[i]);
        memset(f,0x3f,sizeof(int)<<suc);
        for(int j=0;j<c[i];j++){
            for(int sta=0;sta<(1<<c[i]);sta++){
                if(sta>>j&1) g[sta^(1<<j)]=min(g[sta^(1<<j)],g[sta]);
            }
        }
        for(int sta=0;sta<(1<<c[i]);sta++){
            int tmp=(sta|sta<<1)&Mask(c[i])^Mask(c[i]);
            f[sta&Mask(suc)]=min(f[sta&Mask(suc)],__builtin_popcount(sta)+g[tmp]);
        }
    }
    return f[0];
}
#define Count(x) ((x)-(x)/2-(x)/3+(x)/6)

signed main(){
    int n;
    cin>>n;
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        int cnt=Count(r)-Count(l-1);
        if(cnt) ans+=cnt*Solve(n/l);
        // cout<<cnt<<' '<<l<<' '<<r<<endl;
    }
    cout<<ans<<endl;
    return 0;
}