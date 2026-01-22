#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e2+9;

int a[N],c[N][N],sum[N],cnt[1<<21],n,k,s,t;
void Init(){
    for(int i=0;i<=n;i++){
        c[i][0]=1;
        for(int j=1;j<=min(i,k);j++) c[i][j]=c[i-1][j]+c[i-1][j-1],sum[i]+=c[i][j];
    }
}

signed main(){
    int tmp;
    cin>>tmp>>k>>s>>t;
    if((t&s)!=s) return cout<<0<<endl,0;
    for(int i=1,x;i<=tmp;i++){
        cin>>x;
        if((x&s)==s&&(x&t)==x) a[++n]=x;
    }
    Init();

    int lim=t-s,ans=sum[n];
    for(int sta=lim;sta;sta=lim&sta-1){
        int res=0;
        for(int i=1;i<=n;i++) cnt[a[i]&sta]++;
        for(int i=1;i<=n;i++){
            res+=sum[cnt[a[i]&sta]];
            cnt[a[i]&sta]=0;
        }
        ans+=res*(__builtin_popcount(sta)%2?-1:1);
    }
    cout<<ans<<endl;

    return 0;
}