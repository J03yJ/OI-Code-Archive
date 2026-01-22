#include<bits/stdc++.h>

using namespace std;

const int N=12;

int a[N+1][N+1][N+1],f[1<<N][1<<N],n;
vector<int> stt[N+1],vld[1<<N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++) cin>>a[i][j][k];
        }
    }

    for(int sta=0;sta<(1<<n);sta++){
        stt[__builtin_popcount(sta)].push_back(sta);
        for(int i=0;i<n;i++) if(sta>>i&1) vld[sta].push_back(i);
    }
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int sta:stt[i]){
            for(int tta:stt[i]){
                for(int x:vld[sta]){
                    for(int y:vld[tta]){
                        int tmp=f[sta^(1<<x)][tta^(1<<y)];
                        f[sta][tta]=min(f[sta][tta],tmp+a[i][x+1][y+1]);
                    }
                }
            }
        }
    }

    cout<<f[(1<<n)-1][(1<<n)-1]<<endl;

    return 0;
}