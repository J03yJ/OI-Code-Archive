#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e2+9;
const int mod=998244353;

int a[N][N],b[N],c[N][N],n;
inline int H(int *a){
    int res=0;
    for(int i=1;i<=n;i++){
        res=3ll*res%mod;
        res=(res+a[i]+1)%mod;
    }
    return res;
}
inline bool Check(int *a,int *b){
    for(int i=1;i<=n;i++) if(a[i]!=b[i]) return 0;
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) cin>>a[i][j];
        }

        int ans=1;
        for(int i=1;i<=n;i++) ans&=a[1][i];
        map<int,int> mp;
        for(int i=2;i<=n;i++) ans=1ll*ans*(++mp[H(a[i])])%mod;
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++) b[k]=a[i][k]|a[j][k];
                if(Check(a[i],b)) c[i][j]=1;
                if(Check(a[j],b)) c[j][i]=1;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i][j]&&!(c[i][j]||c[j][i])) ans=0;
                for(int k=1;k<=n;k++){
                    if(c[i][k]&&c[j][k]&&!(c[i][j]||c[j][i])) ans=0;
                }
            }
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c[i][j]=c[j][i]=0;

        cout<<ans<<endl;
    }

    return 0;
}