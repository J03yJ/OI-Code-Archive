#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int inv2=(mod+1)/2;
const int inv6=(mod+1)/6;

#define Sum0(x) ((x)+1)
#define Sum1(x) ((x)*((x)+1)%mod*inv2%mod)
#define Sum2(x) ((x)*((x)+1)%mod*((x)*2+1)%mod*inv6%mod)

array<int,3> Solve(int a,int b,int c,int n){
    if(!a) return {(b/c)*Sum0(n)%mod,(b/c)*(b/c)%mod*Sum0(n)%mod,Sum1(n)*(b/c)%mod};
    else if(a>=c||b>=c){
        auto res=Solve(a%c,b%c,c,n);
        int f=res[0],g=res[1],h=res[2];
        return {(Sum1(n)*(a/c)%mod+Sum0(n)*(b/c)%mod+f)%mod,
               (Sum2(n)*(a/c)%mod*(a/c)%mod+Sum1(n)*(a/c)%mod*(b/c)%mod*2%mod+
               Sum0(n)*(b/c)%mod*(b/c)%mod+h*(a/c)%mod*2%mod+f*(b/c)%mod*2%mod+g)%mod,
               (Sum2(n)*(a/c)%mod+Sum1(n)*(b/c)%mod+h)%mod};
    }else{
        int m=(a*n+b)/c;
        auto res=Solve(c,c-b-1,a,m-1);
        int f=res[0],g=res[1],h=res[2];
        return {(m*n%mod-f+mod)%mod,
               (n*m%mod*(m+1)%mod-((m*n%mod-f+mod)%mod+2*f+2*h)%mod+mod)%mod,
               (n*m%mod*(n+1)%mod-(g+f)%mod+mod)%mod*inv2%mod};
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        int a,b,c,n;
        cin>>n>>a>>b>>c;
        auto res=Solve(a,b,c,n);
        cout<<res[0]<<' '<<res[1]<<' '<<res[2]<<endl;
    }
    return 0;
}