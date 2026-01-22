#include<bits/stdc++.h>

using namespace std;

ifstream fin("chicken.in");
ofstream fout("chicken.out");
#define cin fin
#define cout fout

#define int long long
#define bint __int128
const bint inf=1e18;
const bint mod=998244353;

#define S0(x) (((x)+1)%mod)
#define S1(x) (((x)+1)*(x)/2%mod)
bint F(bint n,bint a,bint b,bint c){
    if(!a||!n) return S0(n)*(b/c);
    else if(a>=c||b>=c) return S1(n)*(a/c)+S0(n)*(b/c)+F(n,a%c,b%c,c);
    else return ((a*n+b)/c*n%mod-F((a*n+b)/c-1,c,c-b-1,a)+mod)%mod;
}
void Read(bint &x){int t;cin>>t,x=t;}
void Write(bint x){cout<<(int)x<<endl;}

signed main(){
    bint T;
    Read(T);
    while(T--){
        bint n,a,b,c;
        Read(n),Read(a),Read(b),Read(c);
        bint tmp=(F(n,a,b,c)-(b/c)+mod)%mod*c%mod;
        bint ans=((S1(n)*a%mod+n*b%mod)%mod)%mod;
        Write((ans-tmp+mod)%mod);
    }
    return 0;
}