#include<bits/stdc++.h>

using namespace std;

ifstream fin("substr.in");
ofstream fout("substr.out");
#define cin fin
#define cout fout

const int N=1e6+9;
const int M=4e3+9;

int a[N],n;

namespace Case1{
    int pre[M][M],suf[M][M];
    void Solve(){
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++) pre[i][j]=pre[i][j-1]+(a[i]>=a[j]);
            for(int j=i-1;j>=1;j--) suf[i][j]=suf[i][j+1]+(a[i]>=a[j]);
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;i+j<=n&&i-j+1>=1;j++){
                if(pre[i-j+1][i]!=suf[i+j][i+1]) break ;
                ans=max(ans,j<<1);
            }
        }
        cout<<ans<<endl;
    }
}
namespace Case2{
    void Solve(){
        int ans=0;
        for(int i=1,j=1;i<=n;i=j){
            while(j<=n&&a[i]==a[j]) j++;
            int len=min(n-i+1,(j-i)<<1);
            if(len&1) len^=1;
            ans=max(ans,len);
        }
        cout<<ans<<endl;
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    if(n<=4e3) Case1::Solve();
    else Case2::Solve();

    return 0;
}