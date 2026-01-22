#include<bits/stdc++.h>

using namespace std;

const double eps=1e-13;
const int N=4e2+9;
using ll=long long;

double a[N][N],b[N];
int n;
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

const double A=0.909419792073788;
const double B=0.999948055166504;
const double C=0.000110346530004;
const double D=-0.000018469405977;
const double E=0.999996746207354;
double ans[N];
double F(int n,double T){return 1./(n*B+log(n)*C+sqrt(n)*D)/E+pow(A,n);}
double Get(double T){
    double res=0;
    for(int i=31;i<=100;i++){
        double tmp=F(i,T);
        res+=(tmp-ans[i])*(tmp-ans[i])*exp(i);
    }
    return res;
}

signed main(){    
    // for(int i=-n;i<=n;i++) a[Id(i,0)][Id(i,0)]=a[Id(i,1)][Id(i,1)]=1;
    // for(int i=-n+1;i<n;i++){
    //     vector<int> to[2];
    //     for(int k:{1,2,3}) to[0].push_back(min(i+k,n));
    //     for(int j:to[0]) a[Id(j,1)][Id(i,0)]-=1./to[0].size();
    //     for(int k:{1,2,3}) to[1].push_back(max(i-k,-n));
    //     for(int j:to[1]) a[Id(j,0)][Id(i,1)]-=1./to[1].size();
    // }
    // b[Id(0,0)]=1;
    // Solve(a,b,4*n+2);

    // cout<<fixed<<setprecision(15)<<b[Id(n,1)]-b[Id(-n,0)]<<endl;

    for(n=1;n<=100;n++){
        // cout<<n<<endl;
        for(int i=-n;i<=n;i++) a[Id(i,0)][Id(i,0)]=a[Id(i,1)][Id(i,1)]=1;
        for(int i=-n+1;i<n;i++){
            vector<int> to[2];
            for(int k:{1,2,3}) to[0].push_back(min(i+k,n));
            for(int j:to[0]) a[Id(j,1)][Id(i,0)]-=1./to[0].size();
            for(int k:{1,2,3}) to[1].push_back(max(i-k,-n));
            for(int j:to[1]) a[Id(j,0)][Id(i,1)]-=1./to[1].size();
        }
        b[Id(0,0)]=1;
        Solve(a,b,4*n+2);

        ans[n]=b[Id(n,1)]-b[Id(-n,0)];
        for(int i=1;i<=4*n+2;i++){
            for(int j=1;j<=4*n+2;j++) a[i][j]=0;
            b[i]=0;
        }
    }
    double l=-2,r=2;
    while(r-l>eps){
        double len=(r-l)/3;
        double p1=l+len,p2=r-len;
        cout<<p1<<' '<<p2<<' '<<Get(p1)<<' '<<Get(p2)<<endl;
        if(Get(p1)<Get(p2)) r=p2;
        else l=p1;
    }
    cout<<fixed<<setprecision(15)<<l<<endl;
    for(int i=1;i<=100;i++){
        cout<<i<<" : "<<ans[i]<<'/'<<F(i,l)<<' '<<abs(ans[i]-F(i,l))<<endl;
    }
    cout<<0.00007016947382256606<<'/'<<F(14252,l)<<' '<<abs(0.00007016947382256606-F(14252,l))<<endl;

    return 0;
}