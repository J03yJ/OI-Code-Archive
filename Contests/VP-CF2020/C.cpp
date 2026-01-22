#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int b,c,d,a=0;
        cin>>b>>c>>d;
        for(int i=0;i<=61;i++){
            if(d>>i&1){
                if(c>>i&1) continue ;
                a|=1ll<<i;
            }else if(b>>i&1) a|=1ll<<i;
        }

        if((a|b)-(a&c)!=d) cout<<-1<<endl;
        else cout<<a<<endl;
    }

    return 0;
}