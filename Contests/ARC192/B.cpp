#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int a[N],f[N],g[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int cnt[2]={0,0};
    for(int i=1;i<=n;i++) cnt[a[i]&1]++;

    if(n<=3){
        if(n==1) cout<<"Fennec"<<endl;
        else if(n==2) cout<<"Snuke"<<endl;
        else cout<<(cnt[1]?"Fennec":"Snuke")<<endl;
        return 0;
    }

    if(cnt[1]&1) cout<<"Fennec"<<endl;
    else cout<<"Snuke"<<endl;

    return 0;
}