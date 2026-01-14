#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout

#define int long long
#define endl '\n'
const int N=3e6+9;

int a[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        for(int j=i+i;j<=n;j+=i) a[j]=i;
    }
    int ans=0;
    for(int i=2;i<=n;i++) ans+=i/a[i];
    cout<<ans<<endl;
    for(int i=2;i<=n;i++) cout<<a[i]<<' '<<i<<endl;   

    return 0;
}