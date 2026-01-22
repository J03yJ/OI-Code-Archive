#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e6+9;
const int mod=998244353;

int a[N],tr[N],f[N],n;
void Add(int x,int y){
    x++;
    while(x<=n*2){
        tr[x]=(tr[x]+y)%mod;
        x+=x&-x;
        // cout<<x<<endl;
    }
}
int Ask(int x){
    x++;
    int sum=0;
    while(x){
        sum=(sum+tr[x])%mod;
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){
    if(l>r) return 0;
    return (Ask(r)-Ask(l-1)+mod)%mod;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        a[i]=max(a[i],l);
        a[r]=max(a[r],i);
    }
    for(int i=1;i<=n;i++) a[i]=max(a[i],a[i-1]);
    f[0]=1;
    Add(0,1);
    for(int i=1;i<=n;i++){
        f[i]=Ask(a[i],i-1);
        Add(i,f[i]);
    }
    cout<<f[n]<<endl;

    return 0;
}