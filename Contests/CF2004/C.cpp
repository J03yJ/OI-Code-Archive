#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N];
bool Cmp(int x,int y){
    return x>y;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        sort(a+1,a+n+1,Cmp);
        int ans=0,res=0;
        for(int i=1;i<=n;i+=2) ans+=a[i]-a[i+1];
        for(int i=2;i<=n;i+=2) res+=a[i-1]-a[i];
        ans-=min(res,k);

        cout<<ans<<endl;
        for(int i=1;i<=n;i++) a[i]=0;
    }
}