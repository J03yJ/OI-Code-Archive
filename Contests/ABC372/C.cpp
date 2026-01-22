#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    string s;
    cin>>s;
    s=" "+s;

    int res=0;
    for(int i=1;i<=n-2;i++){
        res+=s.substr(i,3)=="ABC";
    }

    while(m--){
        int pos;char c;
        cin>>pos>>c;
        for(int i=max(1,pos-2);i<=min(pos,n-2);i++){
            res-=s.substr(i,3)=="ABC";
        }
        s[pos]=c;
        for(int i=max(1,pos-2);i<=min(pos,n-2);i++){
            res+=s.substr(i,3)=="ABC";
        }
        cout<<res<<endl;
    }

    return 0;
}