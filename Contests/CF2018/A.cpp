#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=2e5+9;

int a[N],n,k;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];

        int tot=0,sum=0,mx=0;
        for(int i=1;i<=n;i++){
            mx=max(mx,a[i]);
            tot+=a[i];
        }
        for(int i=1;i<=n;i++) sum+=mx-a[i];

        for(int i=(tot+k)/mx;i>=1;i--){
            int x=(tot-1)/i*i;
            if(x+i>tot+k) continue ;
            int d=(tot+k)/i*i-tot,mxx=mx;
            if(sum<d) mxx+=(d-sum+n-1)/n;
            if((tot+d)/i<mxx) continue ;
            cout<<i<<endl;
            break ;
        }
    }

    return 0;
}