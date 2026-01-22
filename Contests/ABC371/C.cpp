#include<bits/stdc++.h>

using namespace std;

const int N=10;

int a[N][N],b[N][N],p[N],w[N][N];

int main(){
    int n;
    cin>>n;
    int m1;
    cin>>m1;
    for(int i=1;i<=m1;i++){
        int x,y;
        cin>>x>>y;
        if(x>y) swap(x,y);
        a[x][y]=1;
    }
    int m2;
    cin>>m2;
    for(int i=1;i<=m2;i++){
        int x,y;
        cin>>x>>y;
        if(x>y) swap(x,y);
        b[x][y]=1;
    }
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) cin>>w[i][j];
    int ans=1e9;
    for(int i=1;i<=n;i++) p[i]=i;
    do{
        int sum=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                int u=p[i],v=p[j];
                if(u>v) swap(u,v);
                if(a[i][j]!=b[u][v]){
                    sum+=w[u][v];
                }
            }
        }
        ans=min(ans,sum);
        // for(int i=1;i<=n;i++) cout<<p[i]<<' ';
        // cout<<" : "<<sum<<endl;
    }while(next_permutation(p+1,p+n+1));
    cout<<ans<<endl;

    return 0;
}