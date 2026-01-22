#include<bits/stdc++.h>

using namespace std;

ifstream fin("set.in");
ofstream fout("set.out");
#define cin fin
#define cout fout

const int N=4e7+9;
const int Mask16=(1<<16)-1;
const int mod=998244353;
int n,p[1<<16];
#define Popc(x) (p[x>>16]+p[x&Mask16])

signed main(){
    cin>>n;

    vector<int> a,b;
    int mask=0,ans=1;
    for(long long i=1;i<=n;i<<=2) mask|=i;
    for(int i=0;i<(1<<16);i++) p[i]=__builtin_popcount(i);
    for(int i=0;i<=n;i++){
        int tmp=(i&mask)^(i>>1&mask);
        if(Popc(tmp)&1) ans=1ll*ans*i%mod,a.push_back(i);
        else b.push_back(i);
    }
    cout<<ans<<endl;

    return 0;
}