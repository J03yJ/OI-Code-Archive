#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
const int mod=998244353;

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

struct Node{
    int lc,rc,epos;
    int f[2];
}tr[N<<1];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define epos(x) tr[x].epos
#define f(x,k) tr[x].f[k]

int cnt;
inline int Allc(){return ++cnt;}
inline void PushUp(int x){
    f(x,0)=Add(Add(Mul(f(lc(x),0),f(rc(x),0)),Mul(f(lc(x),0),f(rc(x),1))),Mul(f(lc(x),1),f(rc(x),0)));
    f(x,1)=Add(Mul(f(lc(x),1),f(rc(x),1)),Mul(Sub(QPow(2,epos(x)),1),Mul(Add(f(lc(x),0),f(lc(x),1)),Add(f(rc(x),0),f(rc(x),1)))));
}
inline void Insert(int &x,int dep,string &s){
    if(!x) x=Allc();
    if(dep==s.size()){
        epos(x)++;
        return PushUp(x);
    }
    if(s[dep]=='A') Insert(lc(x),dep+1,s);
    else Insert(rc(x),dep+1,s);
    PushUp(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    f(0,0)=1;
    int root=Allc(),n;
    
    cin>>n;
    while(n--){
        string s;
        cin>>s;
        Insert(root,0,s);
        cout<<f(root,1)<<endl;
    }

    return 0;
}