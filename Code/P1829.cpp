#include<bits/stdc++.h>

using namespace std;

const int N=1e7+9;
const int p=20101009;
#define int long long

int pri[N],mu[N],pre[N],cnt;
bool b[N];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!b[i]) pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            b[i*pri[j]]=1;
            if(i%pri[j]) mu[i*pri[j]]=-mu[i];
            else{
                mu[i*pri[j]]=0;
                break ;
            }
        }
    }
    mu[1]=1;
    for(int i=1;i<=n;i++) pre[i]=(pre[i-1]+i*i%p*mu[i]%p+p)%p;
}
int calc(int x){
    return x*(x+1)%p*((p+1)/2)%p;
}
int G(int n,int m){
    int ans=0;
    for(int l=1,r;l<=min(n,m);l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+(pre[r]-pre[l-1]+p)%p*calc(n/l)%p*calc(m/l)%p)%p;
    }
    return ans;
}
int F(int n,int m){
    int ans=0;
    for(int l=1,r;l<=min(n,m);l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+(l+r)*(r-l+1)/2%p*G(n/l,m/l))%p;
    }
    return ans;
}

signed main(){
    int n,m;
    cin>>n>>m;
    if(n>m) swap(n,m);
    init(n);
    cout<<F(n,m)<<endl;
}