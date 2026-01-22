#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e6+9;
const int mod=1e9+7;

int sqr,n;

bool ntp[N];
int pri[N],cnt;
void InitP(){
    pri[0]=1;
    for(int i=2;i<=sqr;i++){
        if(!ntp[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=sqr;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break ;
        }
    }
}
int g[3][N],sp[3][N];
int w[N],pos[2][N],tot;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1; 
    }
    return res;
}
void CalcG(){
    sqr=sqrt(n);
    const int INV2=QPow(2,mod-2);
    const int INV6=QPow(6,mod-2);

    for(int i=1;i<=cnt;i++){
        sp[1][i]=(sp[1][i-1]+pri[i])%mod;
        sp[2][i]=(sp[2][i-1]+pri[i]*pri[i]%mod)%mod;
    }
    for(int l=1,r,tmp;l<=n;l=r+1){
        r=n/(n/l);
        w[++tot]=n/l;
        tmp=w[tot]%mod;
        g[1][tot]=(tmp*(tmp+1)%mod*INV2%mod-1+mod)%mod;
        g[2][tot]=(tmp*(tmp+1)%mod*(tmp*2+1)%mod*INV6%mod-1+mod)%mod;
        if(w[tot]<=sqr) pos[0][w[tot]]=tot;
        else pos[1][n/w[tot]]=tot;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1,x,cur;j<=tot&&pri[i]*pri[i]<=w[j];j++){
            x=w[j]/pri[i];
            if(x<=sqr) cur=pos[0][x];
            else cur=pos[1][n/x];
            g[1][j]=(g[1][j]-(g[1][cur]-sp[1][i-1]+mod)%mod*pri[i]%mod+mod)%mod;
            g[2][j]=(g[2][j]-(g[2][cur]-sp[2][i-1]+mod)%mod*pri[i]%mod*pri[i]%mod+mod)%mod;
        }
    }
}
int S(int x,int k){
    if(pri[k]>=x) return 0;
    int cur=x<=sqr?pos[0][x]:pos[1][n/x];
    int ans=((g[2][cur]-g[1][cur]+mod)%mod+(sp[1][k]-sp[2][k]+mod)%mod)%mod;
    for(int i=k+1;i<=cnt&&pri[i]*pri[i]<=x;i++){
        for(int e=1,prin=pri[i];prin<=x;e++,prin*=pri[i]){
            int tmp=prin%mod;
            ans=(ans+tmp*(tmp-1)%mod*(S(x/prin,i)+(e>1))%mod)%mod;
        }
    }
    return ans;
}

signed main(){
    cin>>n;
    sqr=sqrt(n);

    InitP();
    CalcG();
    cout<<(S(n,0)+1)%mod<<endl;

    return 0;
}