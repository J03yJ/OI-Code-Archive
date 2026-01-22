#include<bits/stdc++.h>

using namespace std;

ofstream fout("dfs.in");
#define cout fout

int main(){
    srand(time(0));
    int n=10;
    vector<int> fa(n+1,0);
    cout<<n<<endl;
    for(int i=2;i<=n;i++){
        fa[i]=rand()%(i-1)+1;
        cout<<fa[i]<<' '<<i<<endl;
    }
    return 0;
}