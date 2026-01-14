#include<bits/stdc++.h>

using namespace std;

int main(){
    int l,r;
    cin>>l>>r;
    if(l^r){
        if(l) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }else cout<<"Invalid"<<endl;
}