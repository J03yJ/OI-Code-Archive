#include<bits/stdc++.h>

using namespace std;

ifstream fin("carillon.in");
ofstream fout("carillon.out");
#define cin fin
#define cout fout
#define endl '\n'

const int N=5e7+9;
const int B=1.5e4;
const int mod=5e7+17;
const int cmod=mod-1;
const int g=5;

#define int long long
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
#undef int

int phi[N],pri[N],pre[N],ppre[N],lg[mod],pcnt;
bitset<N> ntp;
void InitP(int lim){
    phi[1]=1,ntp[1]=1;
    pre[0]=ppre[0]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) pri[++pcnt]=i,phi[i]=i-1;
        for(int j=1;j<=pcnt&&pri[j]*i<=lim;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]){
                phi[i*pri[j]]=phi[i]*phi[pri[j]];
            }else{
                phi[i*pri[j]]=phi[i]*pri[j];
                break ;
            }
        }
    }
    for(int i=1;i<=lim;i++) pre[i]=1ll*pre[i-1]*phi[i]%mod;
    for(int i=0,j=1;i<mod-1;i++,j=1ll*j*g%mod) lg[j]=i;
    for(int i=1;i<=lim;i++){
        if(ntp[i]) ppre[i]=ppre[i-1];
        else ppre[i]=(ppre[i-1]+lg[i]-lg[i-1]+cmod)%cmod;
    }
}
#define int long long
int Solve(int n,int m){
    int ans=0;
    for(int i=1;pri[i]<=B&&pri[i]<=min(n,m);i++){
        int x=pri[i];
        ans=(ans+(lg[x]-lg[x-1]+cmod)%cmod*(n/x)%cmod*(m/x)%cmod)%cmod;
    }
    for(int l=B+1,r;l<=min(n,m);l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=((ppre[r]-ppre[l-1]+cmod)%cmod*(n/l)%cmod*(m/l)%cmod+ans)%cmod;
    }
    return QPow(g,ans);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int id,T;
    cin>>id>>T;
    InitP(5e7);
    while(T--){
        int n,m,ans;
        cin>>n>>m;
        ans=QPow(pre[n],m)*QPow(pre[m],n)%mod;
        ans=ans*Solve(n,m)%mod;
        cout<<ans<<endl;
    }

    return 0;
}