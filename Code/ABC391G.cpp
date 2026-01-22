#include<bits/stdc++.h>

using namespace std;

const int N=(1<<15)+9;
const int M=1e3+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}

int f[M][N],g[N],h[N],ans[N],n,m;
int nxt[N][128];
string a;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        memset(f,0,sizeof f);
        memset(ans,0,sizeof ans);
        memset(nxt,0,sizeof nxt);
        
        cin>>a>>m;
        n=a.size(),a="#"+a;

        f[0][0]=1;
        for(int i=1;i<=m;i++){
            for(int sta=0;sta<(1<<n);sta++){
                if(!f[i-1][sta]) continue ;
                for(char ch:{'A','C','G','T'}){
                    if(!nxt[sta][ch]){
                        for(int j=1;j<=n;j++) g[j]=sta>>j-1&1;
                        for(int j=1;j<=n;j++) g[j]+=g[j-1];
                        for(int j=1;j<=n;j++) h[j]=max(h[j-1],max(g[j],g[j-1]+(a[j]==ch)));
                        for(int j=n;j>=1;j--) h[j]-=h[j-1];
                        int tta=0;
                        for(int j=1;j<=n;j++) tta|=h[j]<<j-1;
                        nxt[sta][ch]=tta;
                    }
                    AddAs(f[i][nxt[sta][ch]],f[i-1][sta]);
                }
            }
        }

        for(int sta=0;sta<(1<<n);sta++) AddAs(ans[__builtin_popcount(sta)],f[m][sta]);
        for(int i=0;i<=n;i++) cout<<ans[i]<<endl;
    }
    
    return 0;
}