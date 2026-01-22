#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    mt19937 rng(4649);
    cout<<n<<' '<<m<<endl;
    while(n--) cout<<rng()%998244353<<' ';cout<<endl;

    return 0;
}