//Author:Leftist_G / Shunpower
//Cloud Island & Rain Temperature
//May the force be with you and me.
#include <bits/stdc++.h>
#include "testlib.h"
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=1e5+10;
int tc;
int n,m;
int a[N],b[N];
int mid[N];
vector <int> L,R;
void divide(vector <int> &x,int dep){
    // for(auto i:x) cout<<i<<" "<<a[i]<<" "<<dep<<endl;
    if(dep==-1) return;
    vector <int> lef,rig;
    for(auto i:x){
        a[i]%=(1<<dep);
        if((mid[i]>>dep)&1) rig.pb(i);
        else lef.pb(i);
    }
    sort(lef.begin(),lef.end(),[](int &x,int &y){
        return a[x]<a[y];
    });
    sort(rig.begin(),rig.end(),[](int &x,int &y){
        return a[x]<a[y];
    });
    fr1(i,1,(int)lef.size()-1){
        if(a[lef[i]]==a[lef[i-1]]) quitf(_wa,"Jeremy made a mind jam."); 
    }
    fr1(i,1,(int)rig.size()-1){
        if(a[rig[i]]==a[rig[i-1]]) quitf(_wa,"Jeremy made a mind jam."); 
    }
    divide(lef,dep-1);
    divide(rig,dep-1);
}
void solve(){
    L.clear(),R.clear();
    n=inf.readInt(1,16),m=inf.readInt(1,(1<<n));
    fr1(i,1,m){
        a[i]=inf.readInt(0,(1<<n)-1);
        b[i]=inf.readInt(0,(1<<n)-1);
    }
    // fr1(i,1,m) cout<<"!"<<a[i]<<" "<<b[i]<<endl;
    string s=ans.readToken();
    string t=ouf.readToken();
    bool flg=0;
    if(s!=t){
        if(s=="YES") quitf(_wa,"Jeremy had a solution, but you didn't find that.");
        else quitf(_wa,"Jeremy had no solution, but you found one.");
    }
    else if(t=="NO") return;
    fr1(i,1,m) mid[i]=ouf.readInt(0,(1<<n)-1);
    fr1(i,1,m) L.pb(i),R.pb(i);
    divide(L,n-1);
    fr1(i,1,m) swap(a[i],b[i]);
    divide(R,n-1);
}
int main(int argc, char* argv[]){
#ifdef Shun
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    registerTestlibCmd(argc, argv);
    tc=inf.readInt(1,30);
    while(tc--) solve();
    quitf(_ok,"Zack recalled everything...");
    ET;
}
//ALL FOR Zhang Junhao.
