#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;
const int inf=1e9;

int a[N],f[N][3],n;
int F(int x,int p){
    if(x<p) return x+1;
    else if(x>p) return x-1;
    else return x;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        f[0][1]=f[0][2]=-inf;
        for(int i=1;i<=n;i++){
            f[i][0]=F(f[i-1][0],a[i]);
            f[i][1]=max(f[i-1][0],f[i-1][1]);
            f[i][2]=max(F(f[i-1][1],a[i]),F(f[i-1][2],a[i]));
        }
        cout<<max(f[n][2],f[n][1])<<endl;
        for(int i=1;i<=n;i++) f[i][0]=f[i][1]=f[i][2]=0;
    }
    
    return 0;
}