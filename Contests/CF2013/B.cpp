#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n+1);
        a[0]=-1e9;
        for(int i=1;i<=n;i++) cin>>a[i];
        
        long long ans=0;
        for(int i=1;i<=n;i++) ans+=a[i];
        ans-=2*a[n-1];
        cout<<ans<<endl;
    }
}