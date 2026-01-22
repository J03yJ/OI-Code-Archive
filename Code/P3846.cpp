#include<bits/stdc++.h>

using namespace std;

#define int long long

int QPow(int x,int y,const int mod){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    int p,a,b;
    cin>>p>>a>>b;
    
    unordered_map<int,int> mp;
    int lim=ceil(sqrt(p)),k=QPow(a,lim,p),inva=QPow(a,p-2,p);
    for(int i=0,res=b;i<lim;i++,res=res*inva%p) mp[res]=i;
    for(int i=0,res=1;i<lim;i++,res=res*k%p) if(mp[res]) return cout<<(i*lim+mp[res])%(p-1)<<endl,0;

    cout<<"no solution"<<endl;

    return 0;
}