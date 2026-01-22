#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int l,r;
        cin>>l>>r;
        int ans=(r-l+1)/4;
        if((r-l+1)%4==3&&l%2) ans++;
    }
}