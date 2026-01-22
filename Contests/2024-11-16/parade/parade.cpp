#include<bits/stdc++.h>

using namespace std;

ifstream fin("parade.in");
ofstream fout("parade.out");
#define cin fin
#define cout fout

const int N=3e3+9;

int a[N][N],l[N][N],r[N][N],u[N][N],d[N][N],n,m;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) l[i][j]=a[i][j]?0:l[i][j-1]+1;
        for(int j=m;j>=1;j--) r[i][j]=a[i][j]?0:r[i][j+1]+1;
    }
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++) u[i][j]=a[i][j]?0:u[i-1][j]+1;
        for(int i=n;i>=1;i--) d[i][j]=a[i][j]?0:d[i+1][j]+1;
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]) continue ;
            vector<int> p,q;
            for(int k=0;k<l[i][j];k++) p.push_back(u[i][j-k]);
            for(int k=0;k<u[i][j];k++) q.push_back(l[i-k][j]);
            vector<vector<int>> v(l[i][j]+1);
            for(int k=1;k<u[i][j];k++) v[min(q[k],l[i][j])].push_back(k+1);
            set<int> s;
            for(int k=l[i][j]-1;k;k--){
                for(int x:v[k+1]) s.insert(x);
                auto it=s.upper_bound(p[k]);
                if(it==s.begin()) continue ;
                int tmp=*(--it);
                ans=max(ans,(k+tmp-1)<<1);
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}