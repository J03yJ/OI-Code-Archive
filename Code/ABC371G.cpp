#include<bits/stdc++.h>

using namespace std;

#define Allc(x) x.begin(),x.end()
#define endl '\n'
const int N=2e5+9;

int a[N],fa[N],lim[N],ans[N],vis[N],n;
vector<int> d[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>fa[i];
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n/i;j++) d[i*j].push_back(i);
    }
    for(int i=1;i<=n;i++) lim[i]=-1;

    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        
        vector<int> tmp;
        int cur=i;
        do{
            tmp.push_back(cur);
            vis[cur]=1;
            cur=fa[cur];
        }while(cur!=i);
        
        int m=tmp.size();
        vector<int> p(m);
        iota(Allc(p),0);
        sort(Allc(p),[&tmp](int x,int y){return a[tmp[x]]<a[tmp[y]];});
        for(int pos:p){
            int err=0;
            for(int k:d[m]){
                if((~lim[k])&&lim[k]!=pos%k){
                    err=1;
                    break ;
                }
            }
            if(err) continue ;
            for(int k:d[m]) lim[k]=pos%k;
            
            for(int i=0;i<m;i++) ans[tmp[i]]=a[tmp[(i+pos)%m]];
            break ;
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}