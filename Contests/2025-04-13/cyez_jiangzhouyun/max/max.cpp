#include<bits/stdc++.h>

using namespace std;

ifstream fin("max.in");
ofstream fout("max.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=(1<<20)+9;
template<class S,class T> inline void ChMax(S &x,T y){if(y>x) x=y;}
template<class S,class T> inline void ChMin(S &x,T y){if(y<x) x=y;}

int a[N],b[N],ap[N],an[N],bp[N],bn[N],n,lim;
ll c[N];

signed main(){
    cin>>n;
    lim=1<<n;
    for(int i=0;i<lim;i++) cin>>a[i];
    for(int i=0;i<lim;i++) cin>>b[i];

    memset(ap,-1,sizeof ap);
    memset(an,-1,sizeof an);
    memset(bp,-1,sizeof bp);
    memset(bn,-1,sizeof bn);
    memset(c,-0x3f,sizeof c);
    for(int i=0;i<lim;i++){
        ap[i]=a[i];
        an[i]=a[i];
        bp[i]=b[i];
        bn[i]=b[i];
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
            ChMax(ap[i|(1<<k)],ap[i]);
            ChMin(an[i|(1<<k)],an[i]);
            ChMax(bp[i|(1<<k)],bp[i]);
            ChMin(bn[i|(1<<k)],bn[i]);
        }
    }
    for(int i=0;i<lim;i++){
        if(ap[i]!=-1&&bp[i]!=-1) ChMax(c[i],1ll*ap[i]*bp[i]);
        if(an[i]!=-1&&bn[i]!=-1) ChMax(c[i],1ll*an[i]*bn[i]);
        if(ap[i]!=-1&&bn[i]!=-1) ChMax(c[i],1ll*ap[i]*bn[i]);
        if(an[i]!=-1&&bp[i]!=-1) ChMax(c[i],1ll*an[i]*bp[i]);
    }
    for(int i=1;i<lim;i++) ChMax(c[i],c[i-1]);

    for(int i=0;i<lim;i++) cout<<c[i]<<endl;

    return 0;
}