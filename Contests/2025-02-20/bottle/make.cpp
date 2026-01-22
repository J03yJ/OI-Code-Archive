#include<bits/stdc++.h>

using namespace std;

signed main(){
    mt19937 rng(4649);
    int n=2000;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) cout<<rng()%n+1<<' ';cout<<endl;

    return 0;
}