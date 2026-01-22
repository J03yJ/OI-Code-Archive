#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int inf=1e10;
int a[N];

signed main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    while(q--){
        int pos,k;
        cin>>pos>>k;
        int l=-1,r=inf;
        while(l+1<r){
            int mid=l+r>>1;
            int cnt=(lower_bound(a+1,a+n+1,pos-mid)-a-1);
            cnt+=(a+n+1-upper_bound(a+1,a+n+1,pos+mid));
            cnt=n-cnt;
            // cout<<mid<<' '<<pos<<' '<<cnt<<endl;
            if(cnt<k) l=mid;
            else r=mid;
        }
        cout<<r<<endl;
    }
    return 0;
}