#include<bits/stdc++.h>

using namespace std;

const int N=1e6;

mt19937 rng(4649);

signed main(){
    int n=1e5,m=2e5;
    cout<<n<<' '<<m<<endl;
    for(int i=1;i<=n;i++) cout<<char(rng()%26+'a');cout<<endl;
    for(int i=1;i<=n;i++) cout<<rng()%(100000000)<<' ';cout<<endl;
    while(m--){
        int op=rng()%3+1;
        if(op==1) cout<<1<<' '<<rng()%n+1<<' '<<char(rng()%26+'a')<<endl;
        else if(op==2) cout<<2<<' '<<' '<<rng()%n+1<<rng()%(100000000)<<endl;
        else cout<<3<<' '<<rng()%n+1<<endl;
    }

    return 0;
}