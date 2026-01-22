#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        
        if(c>a) cout<<"No"<<endl;
        else if(b>a*2) cout<<"No"<<endl;
        else if((!c)&&(b&1)) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }

    return 0;
}