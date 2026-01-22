#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    mt19937 rng(4649);
    int n=1<<19,V=1<<19;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) cout<<rng()%V+1<<' ';cout<<endl;

    return 0;
}