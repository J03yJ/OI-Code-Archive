#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;
const int lgN=20;

int a[N],d[N],n;
int st[N][lgN],lg[N];
inline int RGCD(int l,int r){
    int k=lg[r-l+1];
    return __gcd(st[l][k],st[r-(1<<k)+1][k]);
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        for(int i=1;i<n;i++) st[i][0]=d[i]=abs(a[i]-a[i+1]);
        for(int k=1;k<lgN;k++){
            for(int i=1;i<n;i++){
                st[i][k]=__gcd(st[i][k-1],st[i+(1<<k-1)][k-1]);
            }
        }
        for(int i=2;i<n;i++) lg[i]=lg[i>>1]+1;

        long long ans=0;
        for(int i=1,l,r;i<n;i++){
            l=i-1,r=n;
            while(l+1<r){
                int mid=l+r>>1;
                int k=RGCD(i,mid);
                if((k&-k)==k&&k) r=mid;
                else l=mid;
            }
            ans+=n-r;
            l=i-1,r=n;
            while(l+1<r){
                int mid=l+r>>1;
                if(RGCD(i,mid)) r=mid;
                else l=mid;
            }
            ans+=r-i+1;
        }

        cout<<ans+1<<endl;
    }

    return 0;
}