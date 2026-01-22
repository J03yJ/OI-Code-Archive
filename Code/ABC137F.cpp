#include<bits/stdc++.h>

using namespace std;

const int N=3e3+9;

int c[N][N],a[N],ans[N],n;

int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<=n;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%n;
    }
    for(int i=0;i<n;i++){
        if(!a[i]) continue ;
        ans[0]=(ans[0]+a[i])%n;
        for(int j=n-1,pw=1;~j;j--,pw=pw*(n-i)%n){
            ans[j]=(ans[j]+c[n-1][j]*(n-a[i])%n*pw%n)%n;
        }
    }
    for(int i=0;i<n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}