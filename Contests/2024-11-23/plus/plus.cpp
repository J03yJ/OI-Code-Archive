#include<bits/stdc++.h>

using namespace std;

ifstream fin("plus.in");
ofstream fout("plus.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;
const int mod=1ll<<32;

int a[N],b[N],c[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

    while(true){
        for(int i=1;i<=n;i++){
            c[i]=((a[i]^c[i-1])+(b[i]^c[i-1]))%mod;
        }
        if(c[n]==c[0]) break ;
        else c[0]=c[n];
    }

    for(int i=1;i<=n;i++) cout<<c[i]<<' ';cout<<endl;

    return 0;
}