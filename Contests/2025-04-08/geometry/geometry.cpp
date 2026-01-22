#include<bits/stdc++.h>

using namespace std;

ifstream fin("geometry.in");
ofstream fout("geometry.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=1e7+9;
const int B=1e7;

const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}

const int inv2=(mod+1)/2;
const int inv6=(mod+1)/6;
inline int Sum0(int n){return n;}
inline int Sum1(int n){return Mul(Mul(n,n+1),inv2);}
inline int Sum2(int n){return Mul(Mul(n,n+1),Mul(Mul(n,2)+1,inv6));}
inline int Sum3(int n){return Mul(Sum1(n),Sum1(n));}

unordered_map<ll,int> mp[3];
int sum[N][3],phi[N],pri[N],ntp[N],pcnt;
inline void Init(int lim){
    phi[1]=1;
    for(int i=2;i<=lim;i++){
        if(!ntp[i]) phi[i]=i-1,pri[++pcnt]=i;
        for(int j=1;j<=pcnt&&i*pri[j]<=lim;j++){
            ntp[i*pri[j]]=1;
            if(i%pri[j]) phi[i*pri[j]]=phi[i]*phi[pri[j]];
            else{
                phi[i*pri[j]]=phi[i]*pri[j];
                break ;
            }
        }
    }
    for(int i=1;i<=lim;i++){
        sum[i][0]=Add(sum[i-1][0],phi[i]);
        sum[i][1]=Add(sum[i-1][1],Mul(phi[i],i));
        sum[i][2]=Add(sum[i-1][2],Mul(phi[i],Mul(i,i)));
    }
}
inline int S0(int n){
    if(n<=B) return sum[n][0];
    if(mp[0].count(n)) return mp[0][n];
    int res=Sum1(n);
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        SubAs(res,Mul(S0(n/l),Sub(Sum0(r),Sum0(l-1))));
    }
    return mp[0][n]=res;
}
inline int S1(int n){
    if(n<=B) return sum[n][1];
    if(mp[1].count(n)) return mp[1][n];
    int res=Sum2(n);
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        SubAs(res,Mul(S1(n/l),Sub(Sum1(r),Sum1(l-1))));
    }
    return mp[1][n]=res;
}
inline int S2(int n){
    if(n<=B) return sum[n][2];
    if(mp[2].count(n)) return mp[2][n];
    int res=Sum3(n);
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        SubAs(res,Mul(S2(n/l),Sub(Sum2(r),Sum2(l-1))));
    }
    return mp[2][n]=res;
}

inline void Solve(){
    int n;
    cin>>n;
    int m=n%mod,ans=0;
    AddAs(ans,Mul(Mul(m,m+1),S0(n)));
    SubAs(ans,Mul(Add(m,m+1),S1(n)));
    AddAs(ans,S2(n));
    int h=n>>1;
    SubAs(ans,Mul(Mul(m,m+1),S0(h)));
    AddAs(ans,Mul(Mul(2,Add(m,m+1)),S1(h)));
    SubAs(ans,Mul(4,S2(h)));
    MulAs(ans,Mul(3,inv2));
    cout<<ans<<endl;
}

signed main(){
    Init(B);

    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}