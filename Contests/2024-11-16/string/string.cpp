#include<bits/stdc++.h>

using namespace std;

ifstream fin("string.in");
ofstream fout("string.out");
#define cin fin
#define cout fout

const int N=2e3+9;

string s[N];
int res[N][N],n,m,k;
long long rw[N],sum[N],asum;

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>s[i];

    mt19937 rng(time(0));
    for(int i=1;i<=n;i++) rw[i]=rng(),asum+=rw[i];

    for(int i=0;i<m;i++){
        vector<long long> tmp(26,0);
        for(int j=1;j<=n;j++) tmp[s[j][i]-'a']+=rw[j];
        for(int j=1;j<=n;j++) sum[j]+=asum-tmp[s[j][i]-'a'];
    }
    for(int i=1;i<=n;i++){
        long long tmp=asum-rw[i];
        if(k*tmp==sum[i]) cout<<i<<' ';
    }
    cout<<endl;

    return 0;
}