#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int p=1e9+7;

int qpow(int x,int y){
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}
int inv[N];
void init(int n){
    for(int i=1;i<=n;i++) inv[i]=qpow(i,p-2);
}
int C(int n,int m){
    int ans=1;
    for(int i=1;i<=m;i++){
        ans=ans*inv[i]%p;
        ans=ans*((n-i+1)%p)%p;
    }
    return ans;
}

signed main(){
    init(1e6);
    int T;
    cin>>T;
    while(T--){
        int n,m,opt;
        cin>>n>>m>>opt;
        if(!opt) cout<<C(n+m-1,m)<<endl;
        else cout<<C(n,m)<<endl;
    }
    return 0;
}