#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++) cin>>a[i];

        long long ans=0;
        sort(a.begin()+1,a.end());
        for(int i=1,g=-1;i<=n;i++){
            if(a[i]!=g){
                g=a[i];
                for(int j=i+1;j<=n;j++) a[j]=__gcd(a[j],a[i]);
                sort(a.begin()+i+1,a.end());
            }
            ans+=g;
        }

        cout<<ans<<endl;
    }
}