#include<bits/stdc++.h>

using namespace std;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k,ans=0;
        cin>>n>>k;
        if(k==1){
            cout<<n<<endl;
            continue ;
        }
        while(n){
            ans+=n%k;
            n/=k;
        }
        cout<<ans<<endl;
    }

    return 0;
}