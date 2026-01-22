#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=8e1+9;
const int p=998244353;

vector<pair<int,int>> v[N*N];
int a[N],ans[N],res[N][N],cnt;
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second<b.second;
}

signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    map<int,int> mp;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int k=a[j]-a[i];
            if(!mp[k]) mp[k]=++cnt;
            v[mp[k]].push_back({i,j});
        }
    }
    for(int i=1;i<=cnt;i++){
        sort(v[i].begin(),v[i].end(),cmp);
        memset(res,0,sizeof res);
        int cur=0;
        for(int j=1;j<=n;j++){
            res[j][1]=1;
            while(cur<v[i].size()&&v[i][cur].second==j){
                // cout<<j<<' '<<v[i][cur].first<<endl;
                for(int k=1;k<=n;k++) res[j][k]=(res[j][k]+res[v[i][cur].first][k-1])%p;
                cur++;
            }
            for(int k=1;k<=n;k++) ans[k]=(ans[k]+res[j][k])%p;
            // for(int k=1;k<=n;k++) cout<<res[j][k]<<' ';
            // cout<<endl;
        }
        // cout<<endl;
    }

    ans[1]=n;
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}