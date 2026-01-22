#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e5+9;
const int mod=1e9+7;

int a[N],lft[N],n,m,len,k;
ll pre[N];
inline ll F(int l,int r,int k){return 1ll*(r-l+1)*k-(pre[r]-pre[l-1]);}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>len>>k;
    k=len-k;
    for(int i=1;i<=n;i++) cin>>a[i];

    sort(a+1,a+n+1,greater<int>());
    sort(a+1,a+len+1,less<int>());

    ll rem=1ll*m*k,ans=0;
    for(int i=1;i<=len;i++) pre[i]=pre[i-1]+a[i];
    for(int i=1,j=1,lst=a[1];i<=len;i++){
        int l=max(a[i],lst),r=a[i]+m+1;
        while(j<=len&&F(i,j,a[j])<=rem) j++;
        while(l+1<r){
            int mid=ll(l)+ll(r)>>1;
            if(F(i,j-1,mid)<=rem) l=mid;
            else r=mid;
        }
        rem-=l-a[i];
        lst=l;
        ans+=1ll*l*l%mod;
    }

    for(int i=len+1;i<=n;i++) ans+=1ll*a[i]*a[i]%mod;
    cout<<ans%mod<<endl;

    return 0;
}