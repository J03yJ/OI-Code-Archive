#include<bits/stdc++.h>

using namespace std;

ifstream fin("a.in");
ofstream fout("a.out");
#define cin fin
#define cout fout

const int N=5e2+9;
const int inf=1e9;

int a[N][N],g[N][N],n;
long long ans;
inline void ChMin(int &x,int y){
    if(y<x) x=y;
}
void Insert(vector<vector<int>> &f,int x){
    for(int i=1;i<=n;i++){
        if(i==x||f[i][i]==0){
            f[i][x]=a[i][x],f[x][i]=a[x][i];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) ChMin(f[x][i],f[x][j]+f[j][i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) ChMin(f[i][x],f[i][j]+f[j][x]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) ChMin(f[i][j],f[i][x]+f[x][j]);
    }
}
void Solve(int l,int r,vector<vector<int>> &f){
    if(l==r){
        // cout<<l<<" : "<<endl;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==l||j==l) f[i][j]=g[i][j];
                if(f[i][j]==inf) ans--;
                else ans+=f[i][j];
                // cout<<f[i][j]<<' ';
            }
            // cout<<endl;
        }
        return ;
    }
    int mid=(l+r)>>1;
    vector<vector<int>> lf=f,rf=f;
    // cout<<l<<' '<<r<<" : ";
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++) cout<<f[i][j]<<' ';
    //     cout<<endl;
    // }
    for(int i=l;i<=mid;i++) Insert(rf,i);
    for(int i=mid+1;i<=r;i++) Insert(lf,i);
    Solve(l,mid,lf),Solve(mid+1,r,rf);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]==-1) a[i][j]=inf; 
        }
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) g[i][j]=a[i][j];
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(g[i][k]==inf) continue ;
            for(int j=1;j<=n;j++){
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
    vector<vector<int>> f=vector<vector<int>>(n+1,vector<int>(n+1,inf));
    Solve(1,n,f);
    cout<<ans<<endl;

    return 0;
}