#include<bits/stdc++.h>

using namespace std;

#define int long long

ifstream fin("grapes.in");
ofstream fout("grapes.out");
#define cin fin
#define cout fout

const int N=10;

int n,m,a,b;
long long A[N+9][N+9],B[N+9][N+9],C[N+9][N+9],cnt,res;
map<int,bool> vis;

void solve(int sta){
    vis[sta]=1;
    res=min(res,cnt);
    int tta=(1<<(n-a+1)*(m-b+1))-1-sta;
    while(tta){
        int k=tta&-tta;
        if(!vis[sta|k]){
            int pos=0;
            while((1<<pos)<k) pos++;
            int i=pos/(m-b+1),j=pos%(m-b+1);
            for(int ki=1;ki<=a;ki++){
                for(int kj=1;kj<=b;kj++){
                    C[i+ki][j+kj]^=1;
                    cnt+=C[i+ki][j+kj]-(C[i+ki][j+kj]^1);
                }
            }
            solve(sta|k);
            for(int ki=1;ki<=a;ki++){
                for(int kj=1;kj<=b;kj++){
                    C[i+ki][j+kj]^=1;
                    cnt+=C[i+ki][j+kj]-(C[i+ki][j+kj]^1);
                }
            }
        }
        tta-=k;
    }
}

signed main(){
    cin>>n>>m>>a>>b;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>A[i][j];
    }

    long long ans=0;
    for(int d=0;d<30;d++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) B[i][j]=A[i][j]>>d&1;
        }
        if(a==1&&b==1) continue ;
        else if(a==1){
            for(int i=1;i<=n;i++){
                int res=n+1;
                for(int sta=0;sta<(1<<m-b+1);sta++){
                    for(int j=1;j<=m;j++) C[i][j]=B[i][j];
                    for(int j=0;j<=m-b;j++){
                        if(sta>>j&1){
                            for(int k=1;k<=b;k++) C[i][j+k]^=1;
                        }
                    }
                    int tmp=0;
                    for(int j=1;j<=m;j++) tmp+=C[i][j];
                    res=min(res,tmp);
                }
                ans+=res*(1ll<<d);
            }
        }else if(b==1){
            for(int j=1;j<=m;j++){
                int res=n+1;
                for(int sta=0;sta<(1<<n-a+1);sta++){
                    for(int i=1;i<=n;i++) C[i][j]=B[i][j];
                    for(int i=0;i<=n-a;i++){
                        if(sta>>i&1){
                            for(int k=1;k<=a;k++) C[i+k][j]^=1;
                        }
                    }
                    int tmp=0;
                    for(int i=1;i<=n;i++) tmp+=C[i][j];
                    res=min(res,tmp);
                }
                ans+=res*(1ll<<d);
            }
        }else{
            res=n*n+1;
            // for(int sta=0;sta<(1<<(n-a+1)*(m-b+1));sta++){
            //     for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) C[i][j]=B[i][j];
            //     for(int i=0;i<=n-a;i++){
            //         for(int j=0;j<=m-b;j++){
            //             if(sta>>i*(m-b+1)+j&1){
            //                 for(int ki=1;ki<=a;ki++){
            //                     for(int kj=1;kj<=b;kj++) C[i+ki][j+kj]^=1;
            //                 }
            //             }
            //         }
            //     }
            //     int tmp=0;
            //     for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) tmp+=C[i][j];
            //     res=min(res,tmp);
            // }
            cnt=0;
            vis.clear();
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) C[i][j]=B[i][j],cnt+=C[i][j];
            solve(0);
            ans+=res*(1ll<<d);
        }
    }

    cout<<ans<<endl;

    return 0;
}