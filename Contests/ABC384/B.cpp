#include<bits/stdc++.h>

using namespace std;

#define InR(a,l,r) (a<=r&&l<=a)

int main(){
    int n,r;
    cin>>n>>r;
    while(n--){
        int d,a;
        cin>>d>>a;
        if(InR(r,1200,2399)&&d==2) r+=a;
        if(InR(r,1600,2799)&&d==1) r+=a;
    }
    cout<<r<<endl;

    return 0;
}