#include<bits/stdc++.h>

using namespace std;

ifstream fin("sleep.in");
ofstream fout("sleep.out");
#define cin fin
#define cout fout

#define int long long
const int N=20;
int dp[(1<<N)+9],pro[(1<<N)+9];
int qpow(int x,int y,int p){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}
int a[N+9],b[N+9];

signed main(){
    int n,p;
    cin>>n>>p;

    pro[0]=1;
    const int inv=qpow(n,p-2,p);
    for(int sta=0;sta<(1<<n)-1;sta++){
        for(int i=0;i<n;i++) b[i]=a[i]=sta>>i&1;
        for(int i=0;i<n;i++){
            if(!a[i]) continue ;
            b[(i+1)%n]=b[(i+n-1)%n]=1;
        }
        int tta=0;
        for(int i=0;i<n;i++) tta|=b[i]<<i;
        for(int i=0;i<n;i++){
            dp[tta|(1<<i)]=(dp[tta|(1<<i)]+(dp[sta]+pro[sta])%p*inv%p)%p;
            pro[tta|(1<<i)]=(pro[tta|(1<<i)]+pro[sta]*inv%p)%p;
        }
        // cout<<sta<<' '<<dp[sta]<<endl;
    }

    cout<<dp[(1<<n)-1]<<endl;

    return 0;
}