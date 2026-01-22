#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int inf=1e12;

int a[N],d[N],f[N],g[N],n;
vector<int> c[N];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++) a[i]-=i;
    a[++n]=inf;a[0]=-inf;
    for(int i=1,cnt=0;i<=n;i++){
        f[i]=upper_bound(d+1,d+cnt+1,a[i])-d;
        if(f[i]<=cnt) d[f[i]]=min(d[f[i]],a[i]);
        else d[f[i]]=a[i];
        cnt=max(cnt,f[i]);
    }

    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,f[i]);
    cout<<n-ans<<endl;

    c[0].push_back(0);
    for(int i=1;i<=n;i++){
        g[i]=inf;
        c[f[i]].push_back(i);
        for(int lst:c[f[i]-1]){
            if(a[lst]>a[i]||lst>i) continue ;
            vector<int> rpre(i-lst+1,0),rsuc(i-lst+1,0);
            auto pre=rpre.begin()-lst,suc=rsuc.begin()-lst;
            for(int j=lst+1;j<=i;j++) pre[j]=pre[j-1]+abs(a[j]-a[lst]);
            for(int j=i-1;j>=lst;j--) suc[j]=suc[j+1]+abs(a[j]-a[i]);
            for(int j=lst;j<i;j++) g[i]=min(g[i],g[lst]+pre[j]+suc[j+1]);
        }
    }
    cout<<g[n]<<endl;

    return 0;
}