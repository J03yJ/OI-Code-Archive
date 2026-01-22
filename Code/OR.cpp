#include<bits/stdc++.h>

using namespace std;

const int N=(1<<17)+9;
const int mod=998244353;

inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}

int a[N],b[N],n;

inline void And(int *a,int n,bool flag){
    for(int k=0;k<n;k++){
        for(int i=0;i<(1<<n);i++){
            if(i>>k&1) continue ;
            if(!flag) AddAs(a[i],a[i|(1<<k)]);
            else SubAs(a[i],a[i|(1<<k)]);
        }
    }
}

signed main(){
    cin>>n;
    for(int i=0;i<(1<<n);i++) cin>>a[i];
    for(int i=0;i<(1<<n);i++) cin>>b[i];

    And(a,n,0);
    And(b,n,0);
    for(int i=0;i<(1<<n);i++) a[i]=1ll*a[i]*b[i]%mod;
    And(a,n,1);

    for(int i=0;i<(1<<n);i++) cout<<a[i]<<' ';cout<<endl;

    return 0;
}