#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int V=2e7+9;
const int inf=1e18;

int pri[V],ntp[V],phi[V],cnt;
void InitP(int n){
    for(int i=2;i<=n;i++){
        if(!ntp[i]) pri[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&pri[j]*i<=n;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]) phi[pri[j]*i]=phi[i]*phi[pri[j]];
            else{
                phi[pri[j]*i]=phi[i]*pri[j];
                break ;
            }
        }
    }
}

int tr[V],n,m;
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int res=0;
    while(x){
        res+=tr[x];
        x&=x-1;
    }
    return res;
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
    if(Ask(l)==1) return {1,0};
    if(l==r) return {Ask(l)%mod,Ask(l)>=mod};
    pair<int,bool> res=Solve(l+1,r,phi[mod]);
    if(res.second) res.first+=phi[mod];
    return QPow(Ask(l),res.first,mod);
}

signed main(){
    cin>>n>>m;
    for(int i=1,x;i<=n;i++) cin>>x,Add(i,x),Add(i+1,-x);
    
    InitP(2e7); 
    while(m--){
        int op,l,r,k;
        cin>>op>>l>>r>>k;
        if(op==1) Add(l,k),Add(r+1,-k);
        else cout<<Solve(l,r,k).first<<endl;
    }

    return 0;
}