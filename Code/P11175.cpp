#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

#define int long long
const int N=4e4+9;

int pri[N],ntp[N],lg[N],pcnt,mod,g,sq,B;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)
#define cmod (mod-1)
namespace BSGS{
    int invg,tmp;
    __gnu_pbds::gp_hash_table<int,int> mp;
    void Init(){
        B=ceil(sqrt(sq*log(sq)));
        invg=Inv(g),tmp=QPow(g,B);
        for(int i=0,cur=1;i<=ceil(mod/B);i++,cur=cur*tmp%mod){
            mp[cur]=i*B+1;
        }
    }
    int Query(int x){
        for(int i=0,cur=x;i<B;i++,cur=cur*invg%mod){
            if(mp[cur]) return (i+mp[cur]-1)%mod;
        }
        return -1;
    }
}
void InitP(int lim){
    lg[1]=0;
    BSGS::Init();
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,lg[i]=BSGS::Query(i);
        for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            lg[i*pri[j]]=(lg[i]+lg[pri[j]])%cmod;
            if(i%pri[j]==0) break ;
        }
    }
}
int neg1;
int F(int x){
    if(x<=sq) return lg[x];
    int v=mod/x,r=mod%x;
    if(r<x-r) return (neg1+F(r)-lg[v]+cmod)%cmod;
    else return (F(x-r)-lg[v+1]+cmod)%cmod;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>mod>>g;
    InitP(sq=ceil(sqrt(mod)));
    neg1=BSGS::Query(mod-1);
    
    int q;
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        cout<<F(x)<<endl;
    }

    return 0;
}