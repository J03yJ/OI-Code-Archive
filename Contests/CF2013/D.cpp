#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n+1),s(n+1,0),stk;
        for(int i=1;i<=n;i++) cin>>a[i];

        int mx=0,mn=1e18;
        reverse(a.begin()+1,a.end());
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
        #define GetMax(r,l) (s[(r)]-s[(l)]+(r)-(l)-1)/((r)-(l))
        #define GetMin(r,l) (s[(r)]-s[(l)])/((r)-(l))
        #define sback(x) x[x.size()-2]

        stk.push_back(0);
        for(int i=1;i<=n;i++){
            while(stk.size()>1&&GetMin(i,stk.back())>=GetMin(stk.back(),sback(stk))){
                stk.pop_back();
            }
            stk.push_back(i);
        }
        for(int i=1;i<stk.size();i++){
            mx=max(mx,GetMax(stk[i],stk[i-1]));
            mn=min(mn,GetMin(stk[i],stk[i-1]));
        }
        cout<<mx-mn<<endl;
    }

    return 0;
}