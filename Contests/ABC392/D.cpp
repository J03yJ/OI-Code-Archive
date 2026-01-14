#include<bits/stdc++.h>

using namespace std;

const int N=1e2+9;
const int M=1e5+9;

int lim[N],a[N][M],b[N][M],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>lim[i];
        for(int j=1;j<=lim[i];j++) cin>>a[i][j],b[i][a[i][j]]++;
    }

    double ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            double res=0;
            for(int k=1;k<=lim[i];k++){
                res+=(1./lim[i])*(double(b[j][a[i][k]])/lim[j]);
            }
            ans=max(ans,res);
        }
    }

    cout<<fixed<<setprecision(10)<<ans<<endl;

    return 0;
}