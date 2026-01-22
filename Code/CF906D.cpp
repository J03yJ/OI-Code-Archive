#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;

int a[N];

map<int,int> phi;
int Phi(int x){
    if(phi[x]) return phi[x];
    int res=1,tmp=x;
    for(int i=2;i*i<=x;i++){
        if(x%i) continue ;
        x/=i;res*=i-1;
        while(x%i==0) res*=i,x/=i;
    }
    if(x!=1) res*=x-1;
    return phi[tmp]=res;
}

pair<int,bool> QPow(int x,int y,int mod){
    int res=1,flag=0;
    if(x>=mod) x%=mod,flag=1;
    while(y){
        if(y&1){
            res*=x;
            if(res>=mod) res%=mod,flag=1;
        }
        x*=x;
        if(x>=mod) x%=mod,flag=1;
        y>>=1;
    }
    return {res,flag};
}
pair<int,bool> Solve(int l,int r,int mod){
    if(mod==1) return {0,1};
    if(a[l]==1) return {1,0};
    if(l==r) return {a[l]%mod,a[l]>=mod};
    pair<int,bool> res=Solve(l+1,r,Phi(mod));
    if(res.second) res.first+=phi[mod];
    return QPow(a[l],res.first,mod);
}

signed main(){
    int n,mod,m;
    cin>>n>>mod;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<Solve(l,r,mod).first<<endl;
    }
    
    return 0;
}