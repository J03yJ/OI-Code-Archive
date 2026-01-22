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

int F(int a,int b){
    int x=((qpow(10,b)-qpow(10,b-1)+p)%p-qpow(10,a-1)+p)%p;
    int z;
    if(a!=b) z=((qpow(10,b)-qpow(10,b-1)+p)%p-qpow(10,a)+1+p)%p;
    else z=1;
    int y=qpow(10,a-1);
    if(a!=b) y=y*9%p;
    else y=y*8%p;
    return (x+z)*y%p*qpow(2,p-2)%p;
}
int K(int x){
    return qpow(10,x-1)*9%p;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        if(a>b) swap(a,b);
        if(b!=c&&b!=c-1){
            cout<<0<<endl;
            continue ;
        }
        if(b==c) cout<<F(a,b)<<endl;
        else cout<<(K(a)*K(b)%p-F(a,b)+p)%p<<endl;
    }
}