#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ull=unsigned long long;
using bint=__int128;
const int N=1e5+9;

ull a[N],b[64];
inline void Insert(ull x){
    for(int i=63;~i;i--){
        if(~x>>i&1) continue ;
        if(!b[i]){
            b[i]=x;
            break ;
        }else x^=b[i];
    }
}
int n,k;
bint Pow(int x,int k){return !k?1:x*Pow(x,k-1);}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i],Insert(a[i]);

    n=0;
    for(int i=0;i<65;i++) if(b[i]) a[++n]=b[i];

    if(k>=3){
        bint q=0,r=0,mod=1<<n-1;
        for(ull sta=0;sta<(1ll<<n);sta++){
            bint sum=0;
            for(int i=0;i<n;i++) if(sta>>i&1) sum^=a[i+1];
            sum=Pow(sum,k);
            q+=sum>>n-1;
            r+=sum&(mod-1);
            if(r>=mod) q+=r>>n-1,r&=mod-1;
        }
        cout<<ull(q>>1)<<(q&1?".5":"")<<endl;
    }else if(k==1){
        ull tmp=0;
        for(int i=0;i<64;i++) tmp|=b[i];
        cout<<ull(tmp>>1)<<(tmp&1?".5":"")<<endl;
    }else if(k==2){
        ull tmp=0;bint ans=0;
        for(int i=0;i<64;i++) tmp|=b[i];
        for(int i=0;i<64;i++){
            if(~tmp>>i&1) continue ;
            for(int j=0;j<64;j++){
                if(~tmp>>j&1) continue ;
                bool flag=0;
                for(int k=1;k<=n;k++) flag|=(a[k]>>i&1)^(a[k]>>j&1);
                ans+=bint(1)<<(i+j+!flag);
            }
        }
        ans>>=1;
        cout<<ull(ans>>1)<<(ans&1?".5":"")<<endl;
    }

    return 0;
}