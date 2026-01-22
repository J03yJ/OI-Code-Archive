#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;
const int lgV=18;
using ll=long long;

int a[N],b[N],n;

ll ans;
inline void Work(vector<int> &p,vector<int> &q,bool flag){
    for(int k=0;k<lgV;k++){
        int pcnt[2]={0,0},qcnt[2]={0,0};
        for(int i:p) pcnt[(!flag?a[i]:b[i])>>k&1]++;
        for(int i:q) qcnt[(!flag?a[i]:b[i])>>k&1]++;
        ans+=(1ll<<k)*pcnt[0]*qcnt[1];
        ans+=(1ll<<k)*qcnt[0]*pcnt[1];
    }
}
inline void Solve(int dep,vector<int> &v){
    if(v.empty()) return ;
    if(!~dep){
        for(int k=0;k<lgV;k++){
            int cnt[2]={0,0};
            for(int i:v) cnt[a[i]>>k&1]++;
            ans+=(1ll<<k)*cnt[0]*cnt[1];
        }
        return ;
    }
    vector<int> f[2][2];
    for(int i:v) f[a[i]>>dep&1][b[i]>>dep&1].push_back(i);
    Work(f[0][0],f[0][1],0),Work(f[0][0],f[1][0],1);
    Work(f[1][1],f[0][1],1),Work(f[1][1],f[1][0],0);
    for(int i:f[1][1]) f[0][0].push_back(i);
    for(int i:f[1][0]) f[0][1].push_back(i);
    Solve(dep-1,f[0][0]),Solve(dep-1,f[0][1]);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    vector<int> tmp(n);
    iota(tmp.begin(),tmp.end(),1);
    Solve(lgV-1,tmp);

    cout<<ans<<endl;

    return 0;
}