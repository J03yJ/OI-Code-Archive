#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    int ans=0,sum=0;
    for(int i=0;i<n;i++) sum+=a[i];
    for(int sta=0;sta<(1<<n);sta++){
        int tot=0;
        for(int i=0;i<n;i++) if(sta>>i&1) tot+=a[i];
        ans=max(ans,min(tot,sum-tot));
    }

    cout<<sum-ans<<endl;

    return 0;
}