#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
#define int long long

int Pop(int x){
    int ans=0;
    while(x){
        ans+=x&1;
        x>>=1;
    }
    return ans;
}

signed main(){
    string s;
    cin>>s;
    int q;
    cin>>q;
    while(q--){
        int pos;
        cin>>pos;
        pos--;
        int t=pos/s.size();
        pos%=s.size();
        char c=s[pos];
        if(Pop(t)&1) c^=32;
        cout<<c<<' ';
    }
    cout<<endl;

    return 0;
}