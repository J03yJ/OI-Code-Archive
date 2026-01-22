#include<bits/stdc++.h>

using namespace std;

const int N=(1<<20)+9;
const double eps=1e-10;

int n,lim;
double p[N];

int main(){
    cin>>n,lim=1<<n;
    for(int i=0;i<lim;i++) cin>>p[i];
    for(int k=0;k<n;k++){
        for(int i=0;i<lim;i++){
            if(i>>k&1) continue ;
            p[i|(1<<k)]+=p[i];
        }
    }

    double ans=0;
    for(int i=1;i<lim;i++){
        if(1-p[(lim-1)^i]<eps){
            cout<<"INF"<<endl;
            return 0;
        }
        if(__builtin_popcount(i)&1) ans+=1/(1-p[(lim-1)^i]);
        else ans-=1/(1-p[(lim-1)^i]);
    }

    cout<<fixed<<setprecision(10)<<ans<<endl;

    return 0;
}