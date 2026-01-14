#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=4e5+9;
const int K=1e3+9;
const int mod=998244353;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int fac[N],ifac[N];
void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod; 
}
int C(int n,int m){
    if(m>n) return 0;
    else return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

int f[K],g[K],cnt[K][K],cx[K],cy[K],p[K],n,m,k;
int F(int a,int b,int c,int d){return C(c-a+d-b,c-a);}
int Cxk(int a,int b,int c,int d){return a<=c&&b<=d;}
#define P(i) cx[i],cy[i]

signed main(){
    Init(4e5);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=k;i++) cin>>cx[i]>>cy[i];
        for(int i=1;i<=k;i++) cx[i]=n-cx[i],cy[i]=m-cy[i];
        iota(p+1,p+k+1,1);

        sort(p+1,p+k+1,[](int x,int y){
            if(cx[x]!=cx[y]) return cx[x]<cx[y];
            else return cy[x]<cy[y];
        });
        int flag=1;
        if(cx[p[k]]!=n||cy[p[k]]!=m) k++,p[k]=k,cx[p[k]]=n,cy[p[k]]=m;
        else flag=2;
        f[0]=0,g[0]=1;
        for(int i=1;i<=k;i++){
            f[i]=0,g[i]=0;
            for(int j=i-1;~j;j--){
                if(!Cxk(P(p[j]),P(p[i]))){
                    cnt[i][j]=0;
                    continue ;
                }
                cnt[i][j]=F(P(p[j]),P(p[i]));
                vector<int> tmp;
                for(int d=j+1;d<i;d++){
                    if(!Cxk(P(p[j]),P(p[d]))||!Cxk(P(p[d]),P(p[i]))) continue ;
                    cnt[i][j]=(cnt[i][j]-cnt[d][j]*F(P(p[d]),P(p[i]))%mod+mod)%mod;
                }
                int w=f[j]*2+(2*(cx[p[i]]-cx[p[j]])+(cy[p[i]]-cy[p[j]]))*g[j]%mod;
                f[i]=(f[i]+w*cnt[i][j]%mod)%mod;
                g[i]=(g[i]+g[j]*cnt[i][j]%mod)%mod;
            }
        }

        cout<<flag*f[k]%mod*Inv(C(n+m,n))%mod<<endl;
        for(int i=1;i<=k;i++){
            for(int j=0;j<=k;j++){
                cnt[i][j]=0;
            }
        }
    }

    return 0;
}