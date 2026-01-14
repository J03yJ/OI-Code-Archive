#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int p=1e9+7;

int a[N],f[N],lst[3];

signed main(){
    int n;string s;
    cin>>n>>s;
    s=" "+s;
    int ans=1,r=0;
    for(int i=1;i<=n;i++){
        if(s[i]!=s[i-1]) r++;
        else ans=ans*((r+1)/2)%p,r=1;
    }
    ans=ans*((r+1)/2)%p;
    cout<<ans<<endl;
    
    return 0;
}