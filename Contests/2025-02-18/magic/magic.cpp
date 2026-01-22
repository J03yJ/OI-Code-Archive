#include<bits/stdc++.h>

using namespace std;

ifstream fin("magic.in");
ofstream fout("magic.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=4e1+9;
const int M=1e5+9;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}

vector<int> d[M];
inline void InitD(int lim){
    d[0]={0};
    for(int i=1;i<=lim;i++){
        for(int j=i;j<=lim;j+=i) d[j].push_back(i);
    }
}

int op[N],qx[N],qy[N],al[N],ar[N],n,m;

namespace Brute{
    const int V=5e3+9;
    vector<int> f[N][V],lmt[N];
    int ban[V],g[V][V],id[V];
    inline void Solve(){
        InitD(5e3);
        for(int i=0;i<=5e3;i++){
            for(int j=0;j<=i;j++){
                if(!j) g[j][i]=g[i][j]=i;
                else g[j][i]=g[i][j]=g[i-j][j];
            }
        }

        f[0][0]={1};
        for(int i=1;i<=m;i++){
            if(op[i]==1&&qy[i]<=5e3) lmt[qx[i]+1].push_back(i);
            else if(op[i]==2) lmt[qy[i]].push_back(i);
        }
        for(int i=1;i<=n;i++){
            int dist=3;
            for(int j:lmt[i]) if(op[j]==1) ban[qy[j]]=1;
            for(int j:lmt[i]) if(op[j]==2) dist=min(dist,qy[j]-qx[j]);
            for(int p=al[i];p<=ar[i];p++){
                f[i][p]=vector<int>(d[p].size(),0);
                for(int j=0;j<d[p].size();j++) id[d[p][j]]=j;
                for(int q=al[i-1];q<=ar[i-1];q++){
                    if(ban[g[p][q]]) continue ;
                    for(int o=0;o<f[i-1][q].size();o++){
                        if(dist==1){
                            if(g[p][q]==1) AddAs(f[i][p][id[g[p][q]]],f[i-1][q][o]);
                        }else if(dist==2){
                            if(g[p][d[q][o]]==1) AddAs(f[i][p][id[g[p][q]]],f[i-1][q][o]);
                        }else AddAs(f[i][p][id[g[p][q]]],f[i-1][q][o]);
                    }
                }
                for(int j=0;j<d[p].size();j++) id[d[p][j]]=0;
            }
            for(int j:lmt[i]) if(op[j]==1) ban[qy[j]]=0;
        }
        int ans=0;
        for(int p=al[n];p<=ar[n];p++) for(int x:f[n][p]) AddAs(ans,x);
        cout<<ans<<endl;
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>al[i]>>ar[i];
    for(int i=1;i<=m;i++) cin>>op[i]>>qx[i]>>qy[i];

    Brute::Solve();

    return 0;
}