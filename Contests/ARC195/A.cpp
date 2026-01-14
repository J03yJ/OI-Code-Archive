#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],b[N],f[N],g[N],n,m,tot;
vector<int> pos[N],val;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];

    val.push_back(0);
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    for(int i=1;i<=m;i++) val.push_back(b[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    tot=val.size()-1;
    
    for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
    for(int i=1;i<=m;i++) b[i]=lower_bound(val.begin(),val.end(),b[i])-val.begin();
    for(int i=1;i<=tot;i++) pos[i].push_back(0);
    for(int i=1;i<=n;i++) pos[a[i]].push_back(i);
    for(int i=1;i<=tot;i++) pos[i].push_back(n+1);

    f[0]=0,g[m+1]=n+1;
    for(int i=1;i<=m;i++){
        f[i]=*upper_bound(pos[b[i]].begin(),pos[b[i]].end(),f[i-1]);
        if(f[i]==n+1){
            cout<<"No"<<endl;
            return 0;
        }
    }
    for(int i=m;i>=1;i--) g[i]=*--lower_bound(pos[b[i]].begin(),pos[b[i]].end(),g[i+1]);

    f[0]=0,g[m+1]=n+1;
    for(int i=1;i<=m;i++){
        int l=f[i],r=g[i+1];
        int p=*upper_bound(pos[b[i]].begin(),pos[b[i]].end(),l);
        if(p<r){
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    cout<<"No"<<endl;

    return 0;
}