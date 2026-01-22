#include<bits/stdc++.h>

using namespace std;

#define Allc(x) x.begin(),x.end()
#define fir first
#define sec second

double D(pair<int,int> x,pair<int,int> y){
    return sqrt((x.fir-y.fir)*(x.fir-y.fir)+(x.sec-y.sec)*(x.sec-y.sec));
}

int main(){
    int n,s,t;
    cin>>n>>s>>t;
    vector<pair<pair<int,int>,pair<int,int>>> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i].fir.fir>>a[i].fir.sec>>a[i].sec.fir>>a[i].sec.sec;
    a[0]={{0,0},{0,0}};

    double ans=1e18;
    vector<int> p(n+1);
    iota(Allc(p),0);
    do{
        for(int sta=0;sta<(1<<n);sta++){
            auto b=a;
            for(int i=1;i<=n;i++) b[i]=a[p[i]];
            for(int i=0;i<n;i++){
                if(sta>>i&1){
                    swap(b[i+1].fir,b[i+1].sec);
                }
            }
            double res=0;
            for(int i=1;i<=n;i++){
                res+=D(b[i-1].sec,b[i].fir);
            }
            ans=min(ans,res);
        }
    }while(next_permutation(p.begin()+1,p.end()));
    double tmp=0;
    for(int i=1;i<=n;i++) tmp+=D(a[i].fir,a[i].sec);
    cout<<fixed<<setprecision(8)<<ans/s+tmp/t<<endl;

    return 0;
}