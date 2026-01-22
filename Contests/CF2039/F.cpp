#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int lgN=2e1;
const int mod=998244353;

int f[N][lgN],ans[N];
vector<int> d[N];

int F(vector<int> &p){
    if(p.size()==1) return p.back();
    vector<int> q;
    for(int i=0;i<p.size()-1;i++) q.push_back(max(p[i],p[i+1]));
    int x=F(q);
    if(x==-1) return -1;
    int g=0;
    for(int x:p) g=__gcd(x,g);
    if(g==x) return -1;
    else return g;
}

signed main(){
    const int lim=1e2;
    for(int i=1;i<=lim;i++){
        for(int j=i+i;j<=lim;j+=i) d[j].push_back(i);
    }

    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=lim;i++){
            f[i][1]=1;
            for(int j:d[i]){
                for(int k=1;k<lgN;k++){
                    f[i][k]=(f[i][k]+f[j][k-1]*2%mod)%mod;
                }
            }
            for(int k=1;k<lgN;k++) cout<<f[i][k]<<' ';cout<<endl;
            ans[i]=ans[i-1];
            for(int k=1;k<lgN;k++) ans[i]=(ans[i]+f[i][k])%mod;
        }
        cout<<ans[n]<<endl;
    }

    return 0;
}