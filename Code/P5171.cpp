#include<bits/stdc++.h>

using namespace std;

#define int long long
#define bint __int128
#define Clp(x,l,r) min(r,max(x,l))
#define Allc(x) x.begin(),x.end()
const int inf=1e18;


bint F(bint n,bint a,bint b,bint c){
    if(!a||!n) return (n+1)*(b/c);
    else if(c<0) return F(n,-a,-b,-c);
    else if(a>=c||b>=c) return n*(n+1)/2*(a/c)+(n+1)*(b/c)+F(n,a%c,b%c,c);
    else if(a<0||b<0) return n*(n+1)/2*(a/c-1)+(n+1)*(b/c-1)+F(n,a%c+c,b%c+c,c);
    else return (a*n+b)/c*n-F((a*n+b)/c-1,c,c-b-1,a);
}

signed main(){
    int a,b,c;
    cin>>a>>b>>c;
    cout<<(int)F(c/a,-a,c,b)+c/a+1<<endl;
    return 0;
}