#include<bits/stdc++.h>

using namespace std;

ifstream fin("xor.in");
ofstream fout("xor.out");
#define cin fin
#define cout fout

const int N=69;
const int p=998244353;
#define int long long

void F(int &cA,int &cB,int A,int B,int n){
    if(n==1){cA=A;cB=B;return ;}
    int tA,tB;
    F(tA,tB,A,B,n/2);
    if(n%2){
        cA=( (tA*tB%p*2%p) *B%p + ((tA*tA%p+tB*tB%p)%p) *A%p )%p;
        cB=( ((tA*tA%p+tB*tB%p)%p) *B%p + (tA*tB%p*2%p) *A%p )%p;
    }else{
        cA=tA*tB%p*2%p;
        cB=(tA*tA%p+tB*tB%p)%p;
    }
}

int qpow(int x,int y){
    x%=p;
    int m=1;
    while(y){
        if(y&1) m=m*x%p;
        x=x*x%p;
        y>>=1;
    }
    return m;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;

        int l=0;
        while((1ll<<l)<m) l++;
        
        int ans=qpow(2,l)*qpow(m,n)%p;
        for(int i=0;i<l;i++){
            int k=(m-1)>>(i+1),l=(m-1)&((1ll<<(i+1))-1);
            int res=((k<<i)+max(0ll,l-((1ll<<i)-1)))%p;
            int cA,cB;
            F(cA,cB,res,(m%p-res+p)%p,n);
            ans=(ans-((1ll<<i)%p*cA%p)+p)%p;
        }

        cout<<ans<<endl;
    }
}