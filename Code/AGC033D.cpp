#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e2+9;
const int V=2e1+9;

int f[N][N][N][V],c[N][N],n,m;
char a[N][N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }

    for(int u=1;u<=n;u++){
        for(int d=u;d<=n;d++){
            f[u][d][m+1][0]=m;
            for(int l=m;l>=1;l--){
                char flag=0;
                for(int i=u;i<=d;i++){
                    if(!flag) flag=a[i][l];
                    else if(a[i][l]!=flag) flag='!';
                }
                f[u][d][l][0]=flag!='!'?l:l-1;
                if(flag==a[u][l+1]) f[u][d][l][0]=f[u][d][l+1][0];
            }
        }
    }
    if(f[1][n][1][0]==m){
        cout<<0<<endl;
        return 0;
    }
    
    int lim=ceil(log2(n))+ceil(log2(m));
    for(int k=1;k<=lim;k++){
        for(int u=1;u<=n;u++){
            for(int d=u;d<=n;d++) f[u][d][m+1][k]=m;
            for(int l=1;l<=m;l++){
                int p=u;
                for(int d=u;d<=n;d++){
                    f[u][d][l][k]=max(f[u][d][l][k-1],f[u][d][f[u][d][l][k-1]+1][k-1]);
                    #define T(i) min(f[u][(i)][l][k-1],f[(i)+1][d][l][k-1])
                    while(p+1<d&&T(p+1)>=T(p)) p++;
                    f[u][d][l][k]=max(f[u][d][l][k],T(p));
                    #undef T
                }
            }
        }
        if(f[1][n][1][k]==m){
            cout<<k<<endl;
            return 0;
        }
    }

    return 0;
}