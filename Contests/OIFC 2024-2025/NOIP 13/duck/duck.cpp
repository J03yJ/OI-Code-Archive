#include<bits/stdc++.h>

using namespace std;

ifstream fin("duck.in");
ofstream fout("duck.out");
#define cin fin
#define cout fout

#define int long long
const int N=4e5+9;

int a[N],t[N],d[N],n,m;
int Solve(int l,int r){
    int ans=0;
    for(;l<r;l++,r--){
        ans=max(ans,t[l]+t[r]);
        if(t[l]+t[r]<0) return INT_MAX;
    }
    return ans;
}
int Check(int val){
    for(int i=1;i<=n*4;i++){
        d[i]=0;
        int l=max(i-n*2+1,1ll),r=i-1;
        r=min(r,(int)(upper_bound(t+1,t+n*4+1,val-t[i])-t-1));
        l=max(l,(int)(lower_bound(t+1,t+n*4+1,-t[i])-t));
        if((r^i^1)&1) r--;
        if((l^i^1)&1) l++;
        if(l>r) continue ;
        d[(l+i)/2]++,d[(r+i)/2+1]--;
    }
    for(int i=1;i<=n*4;i++){
        d[i]+=d[i-1];
        if(d[i]>=n) return 1;
    }
    return 0;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n*2;i++) cin>>a[i],t[i]=a[i],t[i+n*2]=a[i]-m;

    sort(t+1,t+n*4+1);
    int l=-1,r=2e9;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(Check(mid)) r=mid;
        else l=mid;
    }
    cout<<r<<endl;

    return 0;
}