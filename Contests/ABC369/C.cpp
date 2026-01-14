#include<bits/stdc++.h>

using namespace std;

const int N=4e5+9;

int a[N],b[N],n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    b[0]=-2e9;
    long long ans=n;
    for(int i=1;i<n;i++) b[i]=a[i]-a[i+1];
    for(int i=1,r=0;i<n;i++){
        if(b[i]!=b[i-1]) ans+=1ll*r*(r+1)/2,r=0;
        r++;
        if(i==n-1) ans+=1ll*r*(r+1)/2;
    }

    cout<<ans<<endl;

    return 0;
}