#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int c[N<<1],n,a,b;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>a>>b;
        for(int i=1;i<=n;i++) cin>>c[i],c[i+n]=0;

        int k=__gcd(a,b);
        for(int i=1;i<=n;i++) c[i]%=k;
        sort(c+1,c+n+1);
        for(int i=1;i<=n;i++) c[i+n]=c[i]+k;
        
        int ans=2e9;
        for(int i=1;i<=n;i++) ans=min(ans,c[i+n-1]-c[i]);
        cout<<ans<<endl;
    }

    return 0;
}