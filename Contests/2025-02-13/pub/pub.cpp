#include<bits/stdc++.h>

using namespace std;

ifstream fin("pub.in");
ofstream fout("pub.out");
#define cin fin
#define cout fout

const int N=3e2+9;
using ll=long long;

int f[N][N],res[N],n,mod;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}

signed main(){
    cin>>n>>mod;
    for(int i=1;i<=n;i++){
        f[i][1]=QPow(2,(i-1)*(i-2)/2);
        for(int j=2;j<=i;j++){
            for(int p=1;p<=i-j+1;p++){
                f[i][j]=(f[i][j]+1ll*f[i-p][j-1]*QPow(2,(p-1)*(p-2)/2)%mod)%mod;
            }
        }
        res[i]=QPow(2,i*(i+1)/2);
        for(int j=1;j<i;j++){
            res[i]=(res[i]-1ll*f[i][j]*res[j]%mod+mod)%mod;
        }
    }
    cout<<res[n]<<endl;

    return 0;
}