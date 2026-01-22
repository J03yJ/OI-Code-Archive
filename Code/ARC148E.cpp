#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int mod=998244353;

int a[N],cnt[N],n,k;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);

    if(a[1]+a[n]<k){
        cout<<0<<endl;
        return 0;
    }

    int ans=1,inv=1;
    for(int i=1;i<=n&&a[i]<=(k-1)/2;i++){
        cnt[lower_bound(a+1,a+n+1,k-a[i])-a]++;
    }
    for(int i=n,c=1;i>=1&&a[i]>(k-1)/2;i--){
        ans=ans*c%mod,c++;
        for(int j=1;j<=cnt[i];j++) ans=ans*c%mod,c--;
    }
    a[n+1]=1e9+7ll;
    for(int i=1,j=1;i<=n;i=j){
        while(a[i]==a[j]) j++;
        for(int k=1;k<=j-i;k++) inv=inv*k%mod;
    }
    cout<<ans*QPow(inv,mod-2)%mod<<endl;

    return 0;
}