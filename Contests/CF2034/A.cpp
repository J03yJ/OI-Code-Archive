#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        int ans=2e9;
        for(int r=0;r<min(a,b);r++){
            int x=a-r,y=b-r;
            int z=x*y/__gcd(x,y);
            int res=z+r;
            if(res<a&&res<b) continue ;
            if(res%a!=res%b) continue ;
            ans=min(ans,z+r);
            // cout<<x<<' '<<y<<' '<<z+r<<endl;
        }
        cout<<ans<<endl;
    }

    return 0;
}