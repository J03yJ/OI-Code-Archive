#include<bits/stdc++.h>

using namespace std;

#define int long long
int F(int x){
    int y=sqrt(x);
    while((y+1)*(y+1)<=x) y++;
    while(y*y>x) y--;
    return x-y;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int k;
        cin>>k;
        int l=-1,r=4e18;
        while(l+1<r){
            int mid=l+r>>1;
            if(F(mid)<k) l=mid;
            else r=mid;
        }
        cout<<r<<endl;
    }
    return 0;
}