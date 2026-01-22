#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
int a[N],b[N];

signed main(){
    int n,x,y;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int j=1;j<=n;j++) cin>>b[j];
    
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);

    int cnt1=0,cnt2=0,sum1=0,sum2=0;
    for(int i=n;i>=1;i--){
        if(sum1>x) break ;
        cnt1++;
        sum1+=a[i];
    }
    for(int i=n;i>=1;i--){
        if(sum2>y) break ;
        cnt2++;
        sum2+=b[i];
    }

    cout<<min(cnt1,cnt2)<<endl;

    return 0;
}