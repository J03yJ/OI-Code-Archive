#include<bits/stdc++.h>

using namespace std;

#define int long long
const int p=998244353;

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}

signed main(){
    int n,k;
    cin>>n>>k;
    if(n==1){
        cout<<1<<endl;
        return 0;
    }
    int E=1;
    for(int i=1;i<=k;i++) E=(E*(n-2)%p+(n+1))%p*qpow(n,p-2)%p;
    cout<<E<<endl;
}