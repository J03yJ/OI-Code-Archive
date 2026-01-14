#include<bits/stdc++.h>

using namespace std;

using ll=long long;

signed main(){
    int T;
    cin>>T;
    while(T--){
        ll n,l,r,k;
        cin>>n>>l>>r>>k;
        if(n&1) cout<<l<<endl;
        else{
            if(n==2){
                cout<<-1<<endl;
                continue ;
            }
            ll p=1;
            while(p<=l) p<<=1;
            if(p>r) cout<<-1<<endl;
            else{
                if(k<=n-2) cout<<l<<endl;
                else cout<<p<<endl;
            }
        }
    }

    return 0;
}