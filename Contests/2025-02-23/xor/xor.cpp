#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=1e3+9;
const int lgV=3e1;
const int inf=0x3f3f3f3f;

struct Basis{
    int b[lgV];
    inline bool Insert(int x){
        for(int i=lgV-1;~i;i--){
            if(~x>>i&1) continue ;
            if(!b[i]){
                b[i]=x;
                for(int j=0;j<i;j++) if(b[j]&&(b[i]>>j&1)) b[i]^=b[j];
                for(int j=i+1;j<lgV;j++) if(b[j]&&(b[j]>>i&1)) b[j]^=b[i];
                return 1;
            }else x^=b[i];
        }
        return 0;
    }
    inline int Next(int x){
        int res=0;
        for(int i=lgV-1;~i;i--) if((res^b[i])<=x) res^=b[i];
        for(int i=0;i<lgV;i++){
            if(!b[i]) continue ;
            res^=b[i];
            if(res>>i&1) return res;
        }
        return -1;
    }
}b;

int f[N][N],a[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    memset(f,0x3f,sizeof f);
    for(int i=0;i<=n;i++) f[i][0]=0;
    for(int i=1;i<=n;i++){
        b.Insert(a[i]);
        for(int j=1;j<=n;j++){
            int tmp=b.Next(f[i-1][j-1]);
            if(tmp!=-1) f[i][j]=min(f[i-1][j],tmp);
            else f[i][j]=f[i-1][j];
            cout<<f[i][j]<<" ";
        }
        cout<<endl;
    }

    int ans=0;
    for(int j=1;j<=n;j++) if(f[n][j]!=inf) ans++;
    cout<<ans<<endl;

    return 0;
}