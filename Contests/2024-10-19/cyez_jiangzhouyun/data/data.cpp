#include<bits/stdc++.h>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");
#define cin fin
#define cout fout

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n==2) cout<<1<<endl;
        else if(n&1) cout<<1ll*(n/2)*(n/2+1)<<endl;
        else if(n>>1&1) cout<<1ll*(n/2-2)*(n/2+2)<<endl;
        else cout<<1ll*(n/2-1)*(n/2+1)<<endl;
    }

    return 0;
}