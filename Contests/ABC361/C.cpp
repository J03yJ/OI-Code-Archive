#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N];

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    sort(a+1,a+n+1);
    int ans=1e9+7;
    for(int i=0;i<=k;i++) ans=min(ans,a[n-(k-i)]-a[1+i]);
    cout<<ans<<endl;
}