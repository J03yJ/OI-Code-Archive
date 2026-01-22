#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int mod=998244353;

int f[N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=4,sum1=2,sum2=0;i<=n;i++){
            f[i]=(sum1+sum2)%mod;
            sum1=(sum1+i-1)%mod;
            sum2=(sum2+f[i]*i%mod)%mod;
        }

        int sum=n-1;
        for(int i=1;i<=n;i++) sum=(sum+f[i])%mod;
        cout<<sum<<endl;
    }

    return 0;
}