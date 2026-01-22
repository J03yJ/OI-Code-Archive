#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int B=1e6+9;
const int mod=1e9;
const int dom=1e6;

inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    map<int,int> mp;
    for(int i=1e6;i>=1;i--) if(i%2&&i%5) mp[QPow(i,i)%dom]=i;

    int q;
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        int b=mp[x%dom],p=-1;
        for(int i=0;i<1e3;i++){
            int tmp=b+i*1e6;
            tmp=QPow(tmp,tmp);
            if(tmp==x){
                p=i;
                break ;
            }
        }
        cout<<(p==-1?p:p*1000000+b)<<endl;
    }

    return 0;
}