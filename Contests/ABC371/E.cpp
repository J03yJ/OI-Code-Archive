#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],buc[N];

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int sum=0,ans=0;
    for(int i=1;i<=n;i++){
        sum-=buc[a[i]];
        buc[a[i]]=i;
        sum+=buc[a[i]];
        ans+=sum;
    }
    cout<<ans<<endl;

    return 0;
}