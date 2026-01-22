#include<bits/stdc++.h>

using namespace std;

#define int long long
const int p=998244353;
const int G=3;

int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%p;
        x=x*x%p;
        y>>=1;
    }
    return res;
}

struct Poly{
    vector<int> a,r;
    int n;

    Poly(){}
    Poly(int len){this->reset(len);}

    void reset(int len){
        n=len;
        a=vector<int>(n,0);
        r=vector<int>(n,0);
        for(int i=0;i<n;i++) r[i]=(i&1)*(n>>1)+(r[i>>1]>>1);
    }
    int size(){
        return n;
    }

    int& operator [](int pos){
        return a[pos];
    }

    void NTT(int op){
        for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
        for(int k=1;k<n;k<<=1){
            int gn=qpow(G,(p-1)/(k<<1));
            if(op==-1) gn=qpow(gn,p-2); 
            for(int i=0;i<n;i+=(k<<1)){
                int g=1;
                for(int j=0;j<k;j++,g=g*gn%p){
                    int tmp=a[i+j+k]*g%p;
                    a[i+j+k]=(a[i+j]-tmp+p)%p;
                    a[i+j]=(a[i+j]+tmp)%p;
                }
            }
        }
        if(op==-1) for(int i=0;i<n;i++) a[i]=a[i]*qpow(n,p-2)%p;
    }
    Poly operator *(Poly b){
        Poly ans,tmpa,tmpb;
        tmpa=*this;tmpb=b;
        ans.reset(n);
        tmpa.NTT(1);
        tmpb.NTT(1);
        for(int i=0;i<n;i++) ans[i]=tmpa[i]*tmpb[i]%p;
        ans.NTT(-1);
        return ans;
    }
};

signed main(){
    int n,m;
    cin>>n>>m;
    n++;m++;
    int lim=1;
    while(lim<n+m) lim<<=1;

    Poly f(lim),g(lim);
    for(int i=0;i<n;i++) cin>>f[i];
    for(int i=0;i<m;i++) cin>>g[i];

    Poly ans=f*g;
    for(int i=0;i<n+m-1;i++) cout<<ans[i]<<' ';
    cout<<endl;

    return 0;
}