#include<bits/stdc++.h>

using namespace std;

ofstream fout("graph.in");
#define cout fout

int main(){
    mt19937 rand(time(0));

    int T=4;
    cout<<0<<' '<<T<<endl;
    while(T--){
        int n=200000,m=rand()%1000000000;
        cout<<n<<' '<<m<<endl;
        for(int i=1;i<=n;i++) cout<<rand()%m<<' ';cout<<endl;
        for(int i=1;i<=n;i++) cout<<rand()%m<<' ';cout<<endl;
    }

    return 0;
}