#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1.2e6+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y,int m=mod){if((x+=y)>=m) x-=m;}
inline void SubAs(int &x,int y,int m=mod){if((x-=y)<0) x+=m;}
inline void MulAs(int &x,int y,int m=mod){x=1ll*x*y%m;}
inline int Add(int x,int y,int m=mod){if((x+=y)>=m) x-=m;return x;}
inline int Sub(int x,int y,int m=mod){if((x-=y)<0) x+=m;return x;}
inline int Mul(int x,int y,int m=mod){return 1ll*x*y%m;}

struct FastPow{
    int pw[4][256];
    inline void Init(int x){
        for(int i=0;i<4;i++){
            pw[i][0]=1;
            for(int j=1;j<256;j++) pw[i][j]=Mul(pw[i][j-1],x);
            x=Mul(pw[i][255],x);
        }
    }
    inline int Pow(int y){
        return Mul(Mul(pw[0][y&255],pw[1][y>>8&255]),Mul(pw[2][y>>16&255],pw[3][y>>24&255])); 
    }
}fp;

int x[N],y[N],w[N],ysum[N],n;
int op[N],pos[N],ans[N],t[N],p2[N],q;
vector<int> row[N],col[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>w[i];
    for(int i=1;i<=q;i++) cin>>op[i]>>pos[i];

    const int B=4000;
    for(int i=1;i<=n;i++) row[x[i]].push_back(i);
    for(int i=1;i<=q;i++) if(op[i]==2) col[pos[i]].push_back(i);
    for(int i=1;i<=n;i++) if(row[x[i]].size()<=B) AddAs(ysum[y[i]],w[i]);
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            if(row[pos[i]].size()>B) continue ;
            for(int j:row[pos[i]]){
                SubAs(ysum[y[j]],w[j]);
                MulAs(w[j],w[j]);
                AddAs(ysum[y[j]],w[j]);
            }
        }else ans[i]=ysum[pos[i]];
    }
    
    p2[0]=1;
    for(int i=1;i<=q;i++) p2[i]=Add(p2[i-1],p2[i-1],mod-1);
    for(int i=1;i<=n;i++){
        if(row[i].size()<=B) continue ;
        for(int j=1;j<=q;j++) t[j]=t[j-1]+(op[j]==1&&pos[j]==i);
        for(int j:row[i]){
            fp.Init(w[j]);
            for(int k:col[y[j]]) AddAs(ans[k],fp.Pow(p2[t[k]]));
        }
    }

    for(int i=1;i<=q;i++) if(op[i]==2) cout<<ans[i]<<endl;

    return 0;
}