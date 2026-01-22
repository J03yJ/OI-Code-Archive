#include<bits/stdc++.h>

using namespace std;

ifstream fin("never.in");
ofstream fout("never.out");
#define cin fin
#define cout fout

#define int long long

int f(int x,int y,int z){
    if(!y) return 0;
    if(y&1) return ((f(x,y>>1,z)<<1)+x)%z;
    else return (f(x,y>>1,z)<<1)%z;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,s,t,x,y;
        cin>>n>>s>>t>>x>>y;
        if(t>s&&(t-s)/y>=n) cout<<s+n*y<<endl;
        else if(t<s&&(s-t)/x>=n) cout<<s-n*x<<endl;
        else{
            int z=x+y;
            int d=((f(y,n,z)+s-t)%z+z)%z;
            if(d>=y) d-=z;
            cout<<t+d<<endl;
        } 
    }
}