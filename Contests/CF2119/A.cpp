#include<bits/stdc++.h>

using namespace std;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int x,y,a,b;
        cin>>a>>b>>x>>y;
        if(b==a) cout<<0<<endl;
        else if(b<a){
            if((a^1)==b) cout<<y<<endl;
            else cout<<-1<<endl;
        }else{
            int ans=(b-a)*x;
            int cnt=(b+1)/2-(a+1)/2;
            ans=min(ans,ans+cnt*(y-x));
            cout<<ans<<endl;
        }
    }

    return 0;
}