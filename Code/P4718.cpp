#include<bits/stdc++.h>

using namespace std;

#define int long long

int test[8]={2,325,9375,28178,450775,9780504,1795265022};
int QPow(int x,int y,int p){
    x%=p;
    int res=1;
    while(y){
        if(y&1) res=__int128(1)*res*x%p;
        x=__int128(1)*x*x%p;
        y>>=1;
    }
    return res;
}
bool MR(int x,int y){
    int cnt=0,lim=y-1;
    while(!(lim&1)) lim>>=1,cnt++;
    int val=QPow(x,lim,y);
    if(val==1) return 1;
    for(int i=1;i<=cnt;i++){
        if(val==y-1) return 1;
        val=__int128(1)*val*val%y;
    }
    return 0;
}
int IsP(int x){
    if(x<2) return 0;
    for(int i=0;i<8;i++){
        if(x==test[i]) return 1;
        if(x%test[i]==0) return 0;
        if(x<test[i]) return 1;
        if(!MR(test[i],x)) return 0;
    }
    return 1;
}

mt19937 myrand(4649);
int GCD(int x,int y){
    if(!y) return x;
    else return GCD(y,x%y);
}
int F(int seed,int c,int mod){
    return (__int128(1)*seed*seed+c)%mod;
}
int PR(int x){
    int s=0,t=0,c=myrand()%(x-1)+1;
    int val=1;
    for(int i=1;;i<<=1,s=t,val=1){
        for(int j=1;j<=i;j++){
            t=F(t,c,x);
            val=__int128(1)*val*abs(t-s)%x;
            if(!val) return x;
            if(j%127==0){
                int d=GCD(val,x);
                if(d>1) return d;
            }
        }
        int d=GCD(val,x);
        if(d>1) return d;
    }
    return x;
}
void GetP(int x,int &maxp){
    if(x<=2&&x<=maxp) return ;
    if(IsP(x)){
        maxp=max(maxp,x);
        return ;
    }
    int k=x;
    while(k>=x) k=PR(k);
    while(x%k==0) x/=k;
    GetP(k,maxp);GetP(x,maxp);
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int x,maxp=0;
        cin>>x;
        if(IsP(x)) cout<<"Prime"<<endl;
        else GetP(x,maxp),cout<<maxp<<endl;
    }
    return 0;
}