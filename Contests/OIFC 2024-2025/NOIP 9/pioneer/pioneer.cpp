#include<bits/stdc++.h>

using namespace std;

#define int long long
#define bint __int128

ifstream fin("pioneer.in");
ofstream fout("pioneer.out");
#define cin fin
#define cout fout

const int N=2e5+9;
const int B=61;

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj=1;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int bas[B],n,m,q;
void Insert(int x){
    for(int i=B-1;~i;i--){
        if(x>>i&1){
            if(!bas[i]){
                bas[i]=x;
                break ;
            }
            x^=bas[i];
        }
    }
}
int Min(int x){
    for(int i=B-1;~i;i--) if((x^bas[i])<x) x^=bas[i];
    return x;
}
int Max(int x){
    for(int i=B-1;~i;i--) if((x^bas[i])>x) x^=bas[i];
    return x;
}

int dfn[N],sum[N],f[N],g[N],dcnt;
void DFS(int x,int ic){
    dfn[x]=++dcnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(i==ic) continue ;
        if(!dfn[y]){
            sum[y]=sum[x]^w[i];
            DFS(y,i^1);
        }else Insert(sum[y]^sum[x]^w[i]);
    }
}
int fpre[N][B],gpre[N][B];
bint xpre[N];
void Print(bint x){
    string s="";
    while(x) s+=char('0'+x%10),x/=10;
    if(!s.size()) s.push_back('0');
    reverse(s.begin(),s.end());
    cout<<s<<endl;
}

signed main(){
    cin>>n>>m>>q;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w),AdEg(v,u,w);
    }

    DFS(1,-1);
    for(int i=1;i<=n;i++){
        f[i]=Min(sum[i]),g[i]=Max(sum[i]);
        for(int k=0;k<B;k++){
            fpre[i][k]=fpre[i-1][k]+(f[i]>>k&1);
            gpre[i][k]=gpre[i-1][k]+(g[i]>>k&1);
        }
        xpre[i]=xpre[i-1]+(f[i]^g[i]);
    }

    while(q--){
        int l,r;
        cin>>l>>r;
        bint ans=0,len=r-l+1;
        for(int k=0;k<B;k++){
            bint a=fpre[r][k]-fpre[l-1][k];
            bint b=gpre[r][k]-gpre[l-1][k];
            ans+=(a*(len-b)+b*(len-a))*(1ll<<k);
        }
        ans-=xpre[r]-xpre[l-1];
        ans>>=1;
        Print(ans);
    }

    return 0;
}