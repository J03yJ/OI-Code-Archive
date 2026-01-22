#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e6+9;
const int mod=998244353;
const int p=7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int a[2][N][3],pos[N],n,m,q;
int base[N],val[2][N],res[2];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m>>q;
    for(int k:{0,1}) for(int i=1;i<=n;i++) for(int j:{0,1,2}) cin>>a[k][i][j];

    base[0]=1;for(int i=1;i<=n;i++) base[i]=Mul(base[i-1],p);
    for(int k:{0,1}){
        for(int i=1;i<=m;i++) val[k][i]=1;
        res[k]=1;
    }
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&res[0]==res[1]){
            for(int k:{0,1}){
                for(int t:{0,1,2}){
                    MulAs(res[k],Inv(val[k][a[k][j][t]]));
                    AddAs(val[k][a[k][j][t]],base[j]);
                    MulAs(res[k],val[k][a[k][j][t]]);
                }
            }
            if(res[0]!=res[1]) break ;
            j++;
        }
        for(int k:{0,1}){
            for(int t:{0,1,2}){
                MulAs(res[k],Inv(val[k][a[k][i][t]]));
                SubAs(val[k][a[k][i][t]],base[i]);
                MulAs(res[k],val[k][a[k][i][t]]);
            }
        }
        for(int k:{0,1}){
            for(int t:{0,1,2}){
                MulAs(res[k],Inv(val[k][a[k][j][t]]));
                SubAs(val[k][a[k][j][t]],base[j]);
                MulAs(res[k],val[k][a[k][j][t]]);
            }
        }
        pos[i]=j-1;
    }

    while(q--){
        int l,r;
        cin>>l>>r;
        if(r<=pos[l]) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}