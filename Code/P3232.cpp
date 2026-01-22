#include<bits/stdc++.h>

using namespace std;

const double eps=1e-12;
const int N=5e2+9;

double a[N][N],b[N],e[N*N];
int d[N],u[N*N],v[N*N],n,m;

void Solve(){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(abs(a[j][i])<eps) continue ;
            swap(a[i],a[j]);
            break ;
        }
        if(abs(a[i][i])<eps) assert(0);
        b[i]/=a[i][i];
        for(int j=n;j>=i;j--) a[i][j]/=a[i][i];
        for(int j=i+1;j<=n;j++){
            b[j]-=b[i]*a[j][i];
            for(int k=n;k>=i;k--) a[j][k]-=a[i][k]*a[j][i];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=i-1;j>=1;j--) b[j]-=b[i]*a[j][i];
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        a[u[i]][v[i]]++,a[v[i]][u[i]]++;
        d[u[i]]++,d[v[i]]++;
    }

    b[1]--;
    for(int i=1;i<=n;i++) a[n][i]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]/=d[j];
    for(int i=1;i<=n;i++) a[i][i]--;

    Solve();
    for(int i=1;i<=m;i++) e[i]=b[u[i]]/d[u[i]]+b[v[i]]/d[v[i]];
    sort(e+1,e+m+1,greater<double>());
    double res=0;
    for(int i=1;i<=m;i++) res+=e[i]*i;

    cout<<fixed<<setprecision(3)<<res<<endl;

    return 0;
}