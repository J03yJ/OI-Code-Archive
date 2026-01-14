#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e2+9;

int f[N],x[N],s[N],n,k,dly;

signed main(){
    cin>>n>>k>>dly;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++) s[i]=s[i-1]+x[i];

    memset(f,0,sizeof f);
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j>=max(1ll,i-k+1);j--){
            int pos=max(f[j-1]+dly,x[i]);
            f[i]=min(f[i],f[j-1]+pos*(i-j+1)-(s[i]-s[j-1]));
        }
    }
    cout<<f[n]<<endl;

    return 0;
}