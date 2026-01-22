#include<bits/stdc++.h>

using namespace std;

#define int long long
struct Data{
    vector<int> a;
    int lim,p;
    Data(int n,int m){
        a=vector<int>(m+n/m+1,0);
        lim=n,p=m;
    }
    int &operator [](int x){
        if(x<=p) return a[x];
        else return a[lim/x+p];
    }
};
const int N=5e6+9;
namespace Mu{
    int b[N];
    int Mu(int n){
        int k=ceil(pow(n,double(2)/3));
        int l=ceil(pow(n,double(1)/3));
        auto a=[](int n){return 1;};
        auto c=[](int n){return n==1;};
        auto A=[](int n){return n;};
        auto C=[](int n){return n>=1;};
        Data B(n,k);
        for(int i=1;i<=k;i++) B[i]=B[i-1]+b[i];
        for(int i=l;i>=1;i--){
            int x=n/i;
            int m=sqrt(x),res=0;
            for(int j=1;j<=m;j++) res+=b[j]*(A(x/j)-A(m));
            for(int j=2;j<=m;j++) res+=a(j)*B[x/j];
            B[x]=(C(x)-res)/a(1);
        }
        return B[n];
    }
}
namespace Phi{
    int b[N],pri[N],ntp[N],cnt;
    void Init(int lim){
        b[1]=1;Mu::b[1]=1;
        for(int i=2;i<=lim;i++){
            if(!ntp[i]) pri[++cnt]=i,b[i]=i-1,Mu::b[i]=-1;
            for(int j=1;j<=cnt&&pri[j]*i<=lim;j++){
                ntp[pri[j]*i]=1;
                if(i%pri[j]){
                    b[i*pri[j]]=b[i]*b[pri[j]];
                    Mu::b[i*pri[j]]=Mu::b[i]*Mu::b[pri[j]];
                }
                else{
                    b[i*pri[j]]=b[i]*pri[j];
                    Mu::b[i*pri[j]]=0;
                    break ;
                }
            }
        }
    }
    int Phi(int n){
        int k=ceil(pow(n,double(2)/3));
        int l=ceil(pow(n,double(1)/3));
        auto a=[](int n){return 1;};
        auto c=[](int n){return n;};
        auto A=[](int n){return n;};
        auto C=[](int n){return n*(n+1)/2;};
        Data B(n,k);
        for(int i=1;i<=k;i++) B[i]=B[i-1]+b[i];
        for(int i=l;i>=1;i--){
            int x=n/i;
            int m=sqrt(x),res=0;
            for(int j=1;j<=m;j++) res+=b[j]*(A(x/j)-A(m));
            for(int j=2;j<=m;j++) res+=a(j)*B[x/j];
            B[x]=(C(x)-res)/a(1);
        }
        return B[n];
    }
}

signed main(){
    int T;
    cin>>T;
    Phi::Init(5e6);
    while(T--){
        int n;
        cin>>n;
        cout<<Phi::Phi(n)<<' '<<Mu::Mu(n)<<endl;
    }
    return 0;
}