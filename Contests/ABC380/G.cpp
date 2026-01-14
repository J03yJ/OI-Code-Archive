#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;
const int mod=998244353;

int a[N],tr[N],n,k,ans;
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){
    if(l>r) return 0;
    else return Ask(r)-Ask(l-1);
}

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=Ask(a[i]+1,n);
        Add(a[i],1);
    }
    for(int i=1;i<=n;i++) tr[i]=0;
    for(int i=1,cnt=0;i<=n;i++){
        cnt+=Ask(a[i]+1,n),Add(a[i],1);
        if(i>=k){
            ans=(ans+(sum-cnt)%mod)%mod;
            Add(a[i-k+1],-1);
            cnt-=Ask(1,a[i-k+1]-1);
        }
    }
    ans=ans*QPow(n-k+1,mod-2)%mod;
    int tmp=k*(k-1)/2%mod*QPow(2,mod-2)%mod;
    cout<<(ans+tmp)%mod<<endl;

    return 0;
}