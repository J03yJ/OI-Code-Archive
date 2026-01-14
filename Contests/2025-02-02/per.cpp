#include<bits/stdc++.h>

using namespace std;

ifstream fin("per.in");
ofstream fout("per.out");
#define cin fin
#define cout fout

#define fir(x) (x).first
#define sec(x) (x).second
#define ssiz(x) (signed)x.size()
using ll=long long;
using pll=pair<ll,ll>;
const int N=4e1+9;
const int M=5e6+9;
const int inf=1e9;

int a[N],n;
int lim[N],vis[N];

int lp[N],rp[N],ia[N];
inline void Link(int x){lp[rp[x+1]]=lp[x],rp[lp[x]]=rp[x+1];}
inline void Insert(int x){
    lp[x]=rp[x]=x;
    if(lp[x-1]) Link(x-1);
    if(rp[x+1]) Link(x);
}
inline void GetVec(vector<pll> &res){
    for(int i=1;i<=n;i++){
        if(!rp[i]) continue ;
        res.push_back({i,rp[i]});
        i=rp[i];
    }
}
vector<pll> seg[N];
inline int Len(pll p){return sec(p)-fir(p)+1;}
inline void Upd(pll &p,pll q){
    if(fir(q)<fir(p)) p=q;
    else if(fir(q)==fir(p)) sec(p)+=sec(q);
}
pll f[M],g[M];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],ia[a[i]]=i;
    
    lim[0]=1,f[0]={0,1};
    for(int i=1;i<=n;i++){
        Insert(ia[i]),GetVec(seg[i]),lim[i]=1;
        for(pll p:seg[i]) lim[i]*=Len(p)+1;

        int p=1,q=1,r=1,wf=1;
        vector<int> lst,w({0});
        for(int j=0;j<max(ssiz(seg[i-1]),ssiz(seg[i]));j++){
            if(j>=min(ssiz(seg[i-1]),ssiz(seg[i]))||seg[i][j]!=seg[i-1][j]){
                wf=r=q=p;
                int dlt=ssiz(seg[i-1])-ssiz(seg[i]);
                for(int k=j;k<=j+dlt;k++){
                    q*=Len(seg[i-1][k])+1;
                    lst.push_back(Len(seg[i-1][k])+1);
                }

                int flag=0;
                if(dlt==1) flag=1;
                if(dlt==0&&fir(seg[i-1][j])==fir(seg[i][j])) flag=1;
                if(j<ssiz(seg[i-1])&&flag) wf*=Len(seg[i-1][j])+1;
                if(j<ssiz(seg[i])) r*=Len(seg[i][j])+1;

                for(int k=ssiz(seg[i-1])-1;k>=max(0,j+flag);k--){
                    int x=Len(seg[i-1][k])+1,m=ssiz(w)*x;
                    vector<int> tmp(m);
                    for(int sta=0;sta<m;sta++) tmp[sta]=sta%x+w[sta/x];
                    w=tmp;
                }
                break ;
            }else p*=Len(seg[i][j])+1;
        }

        for(int sta=0;sta<lim[i];sta++) g[sta]={inf,0};
        for(int sta=0;sta<lim[i-1];sta++){
            int low=sta%p,mid=sta%q/p,high=sta/q,cnt=0;
            for(int x:lst) cnt+=mid%x,mid/=x;
            int to=low+(cnt+1)*p+high*r;
            int nto=low+cnt*p+high*r;

            Upd(g[nto],f[sta]);
            Upd(g[to],{fir(f[sta])+w[sta/wf],sec(f[sta])});
        }

        for(int sta=0;sta<lim[i];sta++) f[sta]=g[sta];
    }

    for(int sta=1;sta<=n;sta++) cout<<fir(f[sta])<<' '<<sec(f[sta])<<endl;

    return 0;
}