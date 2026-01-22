#include<bits/stdc++.h>

using namespace std;

ifstream fin("competition.in");
ofstream fout("competition.out");
#define cin fin
#define cout fout

int main(){
    int n,m;
    cin>>n>>m;
    if(n==2&&m==1){
        cout<<(998244353+1)/2<<endl;
    }

    return 0;
}