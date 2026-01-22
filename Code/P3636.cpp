#include<bits/stdc++.h>

using namespace std;

const int p=1e4+7;
const int inv2=5004;
const int inv6=1668;

int f(int n){
    int sum=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        sum=(sum+(r-l+1)*(n/l)%p)%p;
    }
    return sum;
}
int calc2(int n){
    n%=p;
    return n*(n+1)%p*(2*n+1)%p*inv6%p;
}
int F(int n){
    int sum=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        sum=(sum+(calc2(r)-calc2(l-1)+p)%p*f(n/l)%p)%p;
    }
    return sum;
}
int calc(int n){
    n%=p;
    return n*(n+1)%p*inv2%p;
}
int g(int n){
    int sum=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        sum=(sum+(calc(r)-calc(l-1)+p)%p*calc(n/l)%p)%p;
    }
    return sum;
}
int G(int n){
    int sum=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        sum=(sum+(r-l+1)*g(n/l)%p)%p;
    }
    return sum;
}
int H(int n){
    return (12*F(n)+24*G(n))%p;
}

signed main(){
    int l,r;
    cin>>l>>r;
    cout<<(H(r)-H(l-1)+p)%p<<endl;
    return 0;
}