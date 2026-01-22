#include<bits/stdc++.h>

using namespace std;

ifstream fin("seat.in");
ofstream fout("seat.out");
#define cin fin
#define cout fout

#define int long long
const int N=3e5+9;

int a[N],f[1<<21],n,m;
int vis[N],lt[N],gt[N];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int sta=0;sta<(1<<n);sta++){
        for(int i=0;i<n;i++) vis[i+1]=sta>>i&1;
        for(int i=1,l=0;i<=n;i++){
            if(vis[i]) l=a[i];
            else lt[i]=l;
        }
        for(int i=n,r=m+1;i>=1;i--){
            if(vis[i]) r=a[i];
            else gt[i]=r;
        }
        for(int i=0;i<n;i++){
            if(sta>>i&1) continue ;
            f[sta|(1<<i)]=max(f[sta|(1<<i)],f[sta]+gt[i+1]-lt[i+1]);
        }
    }
    cout<<f[(1<<n)-1]<<endl;

    return 0;
}