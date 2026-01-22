#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int p=19260817;

int a[N],d[N];
int mpre[N],apre[N];
int LF(int x,int l,int r){
    // cout<<1ll*d[x]*((apre[r]-apre[l-1]+p)%p)%p<<' '<<mpre[r]<<' '<<mpre[l-1]<<endl;
    return (1ll*d[x]*((apre[r]-apre[l-1]+p)%p)%p-mpre[r]+mpre[l-1]+p)%p;
}
int RF(int x,int l,int r){
    // cout<<1ll*d[x]*((apre[r]-apre[l-1]+p)%p)%p<<' '<<mpre[r]<<' '<<mpre[l-1]<<endl;
    return (mpre[r]-mpre[l-1]-1ll*d[x]*((apre[r]-apre[l-1]+p)%p)%p+2*p)%p;
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=2;i<=n;i++) cin>>d[i],d[i]=(d[i-1]+d[i])%p;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]%=p;

    for(int i=1;i<=n;i++) mpre[i]=(mpre[i-1]+1ll*a[i]*d[i]%p)%p;
    for(int i=1;i<=n;i++) apre[i]=(apre[i-1]+a[i])%p;

    while(m--){
        int x,l,r;
        cin>>x>>l>>r;
        if(x>=r) cout<<LF(x,l,r)<<endl;
        else if(x<=l) cout<<RF(x,l,r)<<endl;
        else cout<<(LF(x,l,x)+RF(x,x,r))%p<<endl;
    }
    
    return 0;
}