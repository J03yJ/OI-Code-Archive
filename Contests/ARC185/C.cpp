#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int G=3;
const int V=1e6;
const int N=1e6+9;

int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
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
            int gn=qpow(G,(mod-1)/(k<<1));
            if(op==-1) gn=qpow(gn,mod-2); 
            for(int i=0;i<n;i+=(k<<1)){
                int g=1;
                for(int j=0;j<k;j++,g=g*gn%mod){
                    int tmp=a[i+j+k]*g%mod;
                    a[i+j+k]=(a[i+j]-tmp+mod)%mod;
                    a[i+j]=(a[i+j]+tmp)%mod;
                }
            }
        }
        if(op==-1) for(int i=0;i<n;i++) a[i]=a[i]*qpow(n,mod-2)%mod;
    }
    Poly operator *(Poly b){
        Poly ans,tmpa,tmpb;
        tmpa=*this;tmpb=b;
        ans.reset(n);
        tmpa.NTT(1);
        tmpb.NTT(1);
        for(int i=0;i<n;i++) ans[i]=tmpa[i]*tmpb[i]%mod;
        ans.NTT(-1);
        return ans;
    }
};

int a[N],n,m;
vector<int> b[N];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    int lim=1;
    while(lim<=m) lim<<=1;

    Poly f(lim);
    for(int i=1;i<=n;i++) f[a[i]]++;
    Poly ans=f*f;
    for(int i=1;i<=n;i++) if(a[i]+a[i]<=m) ans[a[i]+a[i]]--;
    for(int i=1;i<=m;i++) ans[i]=(ans[i]+mod)%mod*qpow(2,mod-2)%mod;

    int x=-1;
    for(int i=1;i<=n;i++){
        if(!ans[m-a[i]]) continue ;
        if(a[i]+a[i]>m){
            x=i;
            break ;
        }else{
            if((ans[m-a[i]]-f[a[i]]*f[m-a[i]-a[i]]%mod+mod)%mod==0){
                continue ;
            }
            x=i;
            break ;
        }
    }
    if(!~x){
        cout<<-1<<endl;
        return 0;
    }

    vector<int> res(1,x);
    int lft=m-a[x];
    for(int i=1;i<=n;i++) if(i!=x) b[a[i]].push_back(i);
    for(int i=1;i<=n;i++){
        if(i==x) continue ;
        if(lft-a[i]<=0) continue ;
        if(a[i]+a[i]==lft){
            if(b[a[i]].size()<=1) continue ;
            res.push_back(i);
            if(b[a[i]].front()==i) res.push_back(b[a[i]].back());
            else res.push_back(b[a[i]].front());
            break ;
        }else{
            if(!b[lft-a[i]].size()) continue ;
            res.push_back(i);
            res.push_back(b[lft-a[i]].front());
            break ;
        }
    }
    if(res.size()<3) assert(0);
    else{
        sort(res.begin(),res.end());
        for(int x:res) cout<<x<<' ';cout<<endl;
    }

    return 0;
}