#include<bits/stdc++.h>

using namespace std;

#define int long long
ifstream fin("divide.in");
ofstream fout("divide.out");
#define cin fin
#define cout fout

const int N=1e3+9;
const int V=5e5+9;
const int mod=1e9+7;

long long f[V],lim;
void Init(){f[0]=1;for(int i=1;i<=lim;i++) f[i]=0;lim=0;}
void Insert(int x){
    lim+=x;
    for(int i=min(lim,50000ll);i>=x;i--) f[i]=(f[i]+f[i-x])%mod;
}
void Erase(int x){
    for(int i=x;i<=min(lim,50000ll);i++) f[i]=(f[i]-f[i-x]+mod)%mod;
    lim-=x;
}

int a[N],b[N],vis[N],n,m;
int Check(int k){
    Init();
    int cnt=0;
    for(int i=1;i<=k;i++) Insert(b[i]),vis[i]=0;
    for(int i=1;i<=n;i++){
        int pos=0;
        for(int j=a[i];j>=0;j--){
            if(f[j]){
                pos=j;
                break ;
            }
        }
        for(int j=k;j>=1;j--){
            if(vis[j]) continue ;
            if(pos<b[j]) continue ;
            if(f[pos-b[j]]){
                Erase(b[j]);
                vis[j]=1;
                pos-=b[j];
                cnt++;
            }
        }
    }
    return cnt==k;
}

signed main(){
    cin>>n;for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;for(int i=1;i<=m;i++) cin>>b[i];
    sort(a+1,a+n+1),sort(b+1,b+m+1);

    int l=0,r=m+1;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) l=mid;
        else r=mid;
    }
    cout<<l<<endl;

    return 0;
}