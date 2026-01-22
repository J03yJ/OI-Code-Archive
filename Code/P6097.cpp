#include<bits/stdc++.h>

using namespace std;

const int N=29;
const int M=(1<<20)+9;
const int p=1e9+9;
#define int long long
#define Popc __builtin_popcount

int a[N][M],b[N][M],c[N][M],n;

void FWT(int a[M],int typ){
    for(int i=1;i<(1<<n);i<<=1){
        for(int j=0;j<(1<<n);j+=(i<<1)){
            for(int k=0;k<i;k++){
                a[i+j+k]=(a[i+j+k]+typ*a[j+k]+p)%p;
            }
        }
    }
}

signed main(){
    cin>>n;
    for(int i=0;i<(1<<n);i++) cin>>a[Popc(i)][i];
    for(int i=0;i<(1<<n);i++) cin>>b[Popc(i)][i];
    for(int i=0;i<=n;i++) FWT(a[i],1),FWT(b[i],1);
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<(1<<n);k++) c[i][k]=(c[i][k]+a[j][k]*b[i-j][k]%p)%p;
        }
    }
    for(int i=0;i<=n;i++) FWT(c[i],-1);
    for(int i=0;i<(1<<n);i++) cout<<c[Popc(i)][i]<<' ';cout<<endl;
    return 0;
}