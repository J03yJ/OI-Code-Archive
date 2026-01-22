#include<bits/stdc++.h>

using namespace std;

const int N=16;

int a[N+9][N+9];
long long w[(1<<N)+9],dp[(1<<N)+9];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cin>>a[i][j];
    }
    
    for(int sta=0;sta<(1<<n);sta++){
        vector<int> v;
        for(int i=1;i<=n;i++) if((sta>>i-1)&1) v.push_back(i);
        for(int i:v){
            for(int j:v) if(i<j) w[sta]+=a[i][j];
        }
        // cout<<w[sta]<<endl;
    }
    dp[0]=0;
    for(int sta=0;sta<(1<<n);sta++){
        vector<int> v;
        for(int i=1;i<=n;i++) if(!((sta>>i-1)&1)) v.push_back(i-1);
        for(int stb=1;stb<(1<<v.size());stb++){
            int cur=0;
            for(int j=0;j<v.size();j++) if((stb>>j)&1) cur|=(1<<v[j]);
            // cout<<cur<<' ';
            dp[sta|cur]=max(dp[sta|cur],dp[sta]+w[cur]);
        }
        // cout<<endl;
    }

    cout<<dp[(1<<n)-1]<<endl;

    return 0;
}