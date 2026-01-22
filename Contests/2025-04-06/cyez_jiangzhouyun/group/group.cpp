#include<bits/stdc++.h>

using namespace std;

ifstream fin("group.in");
ofstream fout("group.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e5+9;
const int mod=1e9+7;
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int a[N],n,k;
inline int Fact(int n){
    int res=1;
    for(int i=1;i<=n;i++) res=1ll*res*i%mod;
    return res;
}
inline int C(int n,int m){return 1ll*Fact(n)*Inv(Fact(m))%mod*Inv(Fact(n-m))%mod;}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);

    map<int,int> cnt;
    ll sum1=0,sum2=0;
    for(int i=1;i<=k;i++) sum1+=a[i];
    for(int i=n;i>=n-k+1;i--) sum2+=a[i];
    int cnt1=0,cnt2=0;
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    for(int i=1;i<=k;i++) if(a[i]==a[k]) cnt1++;
    for(int i=n;i>=n-k+1;i--) if(a[i]==a[n-k+1]) cnt2++;
    cout<<sum2-sum1<<' ';
    if(a[k]!=a[n-k+1]) cout<<1ll*C(cnt[a[k]],cnt1)*C(cnt[a[n-k+1]],cnt2)%mod<<endl;
    else if(a[1]!=a[n]) cout<<1ll*C(cnt[a[k]],cnt1)*C(cnt[a[n-k+1]]-cnt1,cnt2)%mod<<endl;
    else cout<<1ll*C(cnt[a[k]],cnt1)*C(cnt[a[n-k+1]]-cnt1,cnt2)%mod*Inv(2)%mod<<endl;

    return 0;
}