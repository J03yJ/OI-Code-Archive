#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        int x=__gcd(2*k,n);
        if(x==1) cout<<"Yes"<<endl;
        else if(x==2&&(n/2)%x!=0) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}