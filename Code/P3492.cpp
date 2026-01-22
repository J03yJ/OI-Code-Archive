#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e2+9;
const int p=998244353;

int a[N][N],b[N][N],n,m;

int rhash(int a[N][N],int pos){
    int sum=0,mul=1;
    for(int i=1;i<=m;i++) sum+=a[pos][i]<<3,mul=mul*a[pos][i]%p;
    return sum+mul;
}
int chash(int a[N][N],int pos){
    int sum=0,mul=1;
    for(int i=1;i<=n;i++) sum+=a[i][pos]<<3,mul=mul*a[i][pos]%p;
    return sum+mul;
}
bool check(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>b[i][j];
    map<int,int> ma,mb;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ma[a[i][j]]++,mb[b[i][j]]++;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(ma[a[i][j]]!=mb[a[i][j]]) return 0; 
    map<int,int> ca,cb,ra,rb;
    for(int i=1;i<=n;i++) ra[rhash(a,i)]++,rb[rhash(b,i)]++;
    for(int i=1;i<=m;i++) ca[chash(a,i)]++,cb[chash(b,i)]++;
    for(int i=1;i<=n;i++) if(ra[rhash(a,i)]!=rb[rhash(a,i)]) return 0;
    for(int i=1;i<=m;i++) if(ca[chash(a,i)]!=cb[chash(a,i)]) return 0;
    return 1;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        if(check()) cout<<"TAK"<<endl;
        else cout<<"NIE"<<endl;
    }
}