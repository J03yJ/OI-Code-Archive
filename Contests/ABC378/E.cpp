#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],tr[N],n,m;
void Add(int x,int k){
    x++;
    while(x<=m){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    x++;
    int ans=0;
    while(x){
        ans+=tr[x];
        x&=x-1;
    }
    return ans;
}
int Ask(int l,int r){
    if(l>r) return 0;
    return Ask(r)-Ask(l-1);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]=(a[i]+a[i-1])%m;
    }

    int ans=0;
    for(int i=1,sum=0;i<=n;i++){
        Add(a[i],1);
        sum+=a[i];
        ans+=a[i]*(i+1)-sum+Ask(a[i]+1,m-1)*m;
    }
    cout<<ans<<endl;

    return 0;
}