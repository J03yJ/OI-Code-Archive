#include<bits/stdc++.h>

using namespace std;

bool IsPrime(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0) return 0;
    }
    return 1;
}
int F(int x){
    for(int i=x;i>=0;i--){
        if(i&1) continue ;
        if(IsPrime(i>>1)) return (i>>1)-1;
    }
    return 0;
}

signed main(){
    int mx=-1e9;
    for(int i=1;i<=100000;i++) mx=max(mx,i/3-1-F(i));
    cout<<mx<<endl;
    return 0;
}