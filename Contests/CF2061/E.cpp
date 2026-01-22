#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],b[N],p[N],pp[N],cc[N],f[N][11],n,m,t;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>t;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int k=0;k<m;k++) p[1<<k]=k+1;
        for(int k=0;k<(1<<m);k++) pp[k]=__builtin_popcount(k);

        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++) f[i][j]=INT_MAX;
            vector<int> tmp(1<<m,a[i]);
            for(int sta=1;sta<(1<<m);sta++){
                tmp[sta]=tmp[sta&sta-1]&b[p[sta&-sta]];
                f[i][pp[sta]]=min(f[i][pp[sta]],tmp[sta]);
            }
            f[i][0]=tmp[0];
        }

        long long ans=0;
        priority_queue<pair<int,int>> q;
        for(int i=1;i<=n;i++) cc[i]=0,ans+=f[i][0],q.push({f[i][0]-f[i][1],i});
        while(t--&&q.size()){
            ans-=q.top().first;
            int x=q.top().second;
            q.pop();
            if(++cc[x]<m) q.push({f[x][cc[x]]-f[x][cc[x]+1],x});
        }

        cout<<ans<<endl;
        for(int i=1;i<=n;i++){
            cc[i]=0;
            for(int j=0;j<=m;j++) f[i][j]=0;
        }
    }

    return 0;
}