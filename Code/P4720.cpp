#include<bits/stdc++.h>

using namespace std;

#define int long long
const int INF=LONG_LONG_MAX;

int QPow(int x,int y,const int mod){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
pair<int,int> ExGCD(int a,int b){
    if(!b) return {1,0};
    pair<int,int> tmp=ExGCD(b,a%b);
    return {tmp.second,tmp.first-a/b*tmp.second};
}
vector<pair<int,int>> BreakDown(int k){
    vector<pair<int,int>> ans;
    for(int i=2;i*i<=k;i++){
        if(k%i) continue ;
        ans.push_back({i,0});
        while(k%i==0) ans.back().second++,k/=i;
    }
    if(k!=1) ans.push_back({k,1});
    return ans;
}
#define Inv(x,mod) ((ExGCD(x,mod).first%mod+mod)%mod)

int CRT(vector<int> a,vector<int> m){
    int mod=1;
    for(int x:m) mod*=x;

    int res=0;
    for(int i=0;i<a.size();i++){
        int k=mod/m[i];
        res=(res+k*Inv(k,m[i])%mod*a[i]%mod)%mod;
    }
    
    return res;
}
int FacExcp(int n,int p,int mod){
    if(n<=1) return 1;
    int res=1;
    for(int i=1;i<=mod;i++) if(i%p) res=res*i%mod;
    res=QPow(res,n/mod,mod);
    for(int i=1;i<=n%mod;i++) if(i%p) res=res*i%mod;
    return FacExcp(n/p,p,mod)*res%mod;
}
int FacCnt(int n,int p){
    if(n<=1) return 0;
    else return FacCnt(n/p,p)+n/p;
}
int ExLucas(int n,int m,int mod){
    vector<pair<int,int>> p=BreakDown(mod);
    vector<int> a,t;
    for(pair<int,int> pr:p){
        int pri=pr.first,c=pr.second,pn=QPow(pri,c,INF);
        // cout<<pri<<' '<<c<<' '<<pn<<endl;
        t.push_back(pn);
        int tmp=FacExcp(n,pri,pn)*Inv(FacExcp(m,pri,pn),pn)%pn*Inv(FacExcp(n-m,pri,pn),pn)%pn;
        // cout<<FacExcp(n,pri,pn)<<' '<<Inv(FacExcp(m,pri,pn),pn)%pn<<' '<<Inv(FacExcp(n-m,pri,pn),pn)<<endl;
        tmp=tmp*QPow(pri,FacCnt(n,pri)-FacCnt(m,pri)-FacCnt(n-m,pri),pn)%pn;
        // cout<<FacCnt(n,pri)<<' '<<FacCnt(m,pri)<<' '<<FacCnt(n-m,pri)<<endl;
        // cout<<tmp<<endl;
        a.push_back(tmp);
    }
    return CRT(a,t);
}

signed main(){
    int n,m,mod;
    cin>>n>>m>>mod;
    cout<<ExLucas(n,m,mod)<<endl;

    return 0;
}