#include<bits/stdc++.h>

using namespace std;

const int inf=1e9;

int main(){
    int n;
    cin>>n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>b[i]>>a[i];

    int sum=0;
    for(int i=0;i<n;i++) sum+=a[i];
    if(sum%3){
        cout<<-1<<endl;
        return 0;
    }

    int lim=sum/3;
    vector<vector<int>> dp(lim+1,vector<int>(lim+1,inf));
    vector<vector<int>> ldp;
    dp[0][0]=0;

    for(int i=0;i<n;i++){
        ldp=dp;
        dp=vector<vector<int>>(lim+1,vector<int>(lim+1,inf));
        for(int j=0;j<=lim;j++){
            for(int k=0;k<=lim;k++){
                if(j+a[i]<=lim){
                    dp[j+a[i]][k]=min(dp[j+a[i]][k],ldp[j][k]+(b[i]!=1));
                }
                if(k+a[i]<=lim){
                    dp[j][k+a[i]]=min(dp[j][k+a[i]],ldp[j][k]+(b[i]!=2));
                }
                dp[j][k]=min(dp[j][k],ldp[j][k]+(b[i]!=3));
            }
        }
    }
    if(dp[lim][lim]==inf) cout<<-1<<endl;
    else cout<<dp[lim][lim]<<endl;

    return 0;
}