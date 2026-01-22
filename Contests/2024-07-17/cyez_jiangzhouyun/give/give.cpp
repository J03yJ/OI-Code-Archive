#include<bits/stdc++.h>

using namespace std;

ifstream fin("give.in");
ofstream fout("give.out");
#define cin fin
#define cout fout

#define int long long

const int N=5e3+9;
const int p=2;
int a[N],dp[N][N];

signed main(){
    int T;
    cin>>T;
    while(T--){
        int m,s,n;
        cin>>m>>s>>n;
        if(n>5e3||m>5e3||s>5e3){
            cout<<0<<endl;
            continue ;
        }
        for(int i=1;i<=n;i++) cin>>a[i];
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                for(int k=a[j];k<=s;k++) dp[i][k]=(dp[i][k]+dp[i-1][k-a[j]])%p;
            }
        }
        cout<<dp[m][s]<<endl;
    }
}