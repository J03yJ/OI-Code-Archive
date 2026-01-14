#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        int l3=max(l1,l2);
        int r3=min(r1,r2);
        if(r3<l3){
            cout<<1<<endl;
            continue ;
        }
        int ans=r3-l3;
        if(l1<l3) ans++;
        if(l2<l3) ans++;
        if(r1>r3) ans++;
        if(r2>r3) ans++;
        cout<<ans<<endl;
    }
}