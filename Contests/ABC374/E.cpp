#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e2+9;
const int inf=1e18;

#define w(a,b) (double(a)/b)
int a[N],b[N],p[N],q[N],g[N],n,lim;
bool Check(int k){
    int sum=0;
    // cout<<k<<" : "<<endl;
    for(int i=1;i<=n;i++){
        int res=inf;
        for(int j=0;j<=a[i]/g[i];j++){
            int tmp=j*q[i]+(max(k-j*b[i],0ll)+a[i]-1)/a[i]*p[i];
            res=min(res,tmp);
        }
        sum+=res;
        // cout<<res<<' ';
    }
    // cout<<endl;
    return sum<=lim;
}

signed main(){
    cin>>n>>lim;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>p[i]>>b[i]>>q[i];
        if(w(a[i],p[i])<w(b[i],q[i])) swap(a[i],b[i]),swap(p[i],q[i]);
        g[i]=__gcd(a[i],b[i]);
    }

    int l=0,r=lim*100+1;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) l=mid;
        else r=mid;
    }
    cout<<l<<endl;

    return 0;
}