#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int a[N],pos[N],p[N],n,m,ans;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>pos[i];
    for(int i=1;i<=m;i++) cin>>a[i];
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[](int x,int y){return pos[x]<pos[y];});

    p[m+1]=m+1,pos[m+1]=n+1;
    pos[0]=1,p[0]=0;
    int lft=0;
    for(int i=m;i>=0;i--){
        lft+=pos[p[i+1]]-pos[p[i]];
        int tmp=min(lft,a[p[i]]);
        ans+=tmp*pos[p[i]];
        lft-=tmp;
        a[p[i]]-=tmp;
        if(a[p[i]]>0){
            cout<<-1<<endl;
            return 0;
        }
    }
    if(lft>0){
        cout<<-1<<endl;
        return 0;
    }

    cout<<n*(n+1)/2-ans<<endl;

    return 0;
}