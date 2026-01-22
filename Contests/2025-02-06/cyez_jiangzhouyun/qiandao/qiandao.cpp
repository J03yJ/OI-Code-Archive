#include<bits/stdc++.h>

using namespace std;

ifstream fin("qiandao.in");
ofstream fout("qiandao.out");
#define cin fin
#define cout fout
#define endl '\n'

const double eps=1e-13;
const int N=2e3+9;
using ll=long long;

double a[N][N],b[N];
ll n;
void Solve(double a[N][N],double b[N],int n){
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
inline int Id(int x,int flag){return flag?x+3*n+2:x+n+1;}

signed main(){
    cin>>n;

    if(n<=300){
        for(int i=-n;i<=n;i++) a[Id(i,0)][Id(i,0)]=a[Id(i,1)][Id(i,1)]=1;
        for(int i=-n+1;i<n;i++){
            vector<int> to[2];
            for(int k:{1,2,3}) to[0].push_back(min(i+k,signed(n)));
            for(int j:to[0]) a[Id(j,1)][Id(i,0)]-=1./to[0].size();
            for(int k:{1,2,3}) to[1].push_back(max(i-k,signed(-n)));
            for(int j:to[1]) a[Id(j,0)][Id(i,1)]-=1./to[1].size();
        }
        b[Id(0,0)]=1;
        Solve(a,b,4*n+2);
        cout<<fixed<<setprecision(15)<<b[Id(n,1)]-b[Id(-n,0)]<<endl;
    }else cout<<fixed<<setprecision(15)<<-6./(-6*n+sqrt(3)+3)<<endl;

    return 0;
}