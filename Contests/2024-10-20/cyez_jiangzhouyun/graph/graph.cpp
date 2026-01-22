#include<bits/stdc++.h>

using namespace std;

ifstream fin("graph.in");
ofstream fout("graph.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e5+9;

int dis[N],a[N],vis[N],n;
vector<int> v[N];
pair<int,int> DFS(int x){
    for(int i=1;i<=n;i++) dis[i]=0;
    // for(int i=1;i<=10;i++) vis[i]=0;
    dis[x]=1;
    queue<int> q;
    q.push(x);
    while(q.size()){
        int x=q.front();
        q.pop();
        if(!dis[x-1]&&x!=1) dis[x-1]=dis[x]+1,q.push(x-1);
        if(!dis[x+1]&&x!=n) dis[x+1]=dis[x]+1,q.push(x+1);
        // if(vis[a[x]]) continue ;
        // vis[a[x]]=1;
        for(int y:v[a[x]]){
            if(!dis[y]) dis[y]=dis[x]+1,q.push(y);
        }
    }
    pair<int,int> ans={0,0};
    for(int i=1;i<=n;i++){
        if(dis[i]>ans.first) ans.first=dis[i],ans.second=1;
        else if(dis[i]==ans.first) ans.second++;
    }
    ans.first--;
    return ans;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        a[i]=c-'0'+1;
        v[a[i]].push_back(i);
    }

    pair<int,int> ans={0,0};
    for(int i=1;i<=n;i++){
        auto res=DFS(i);
        if(res.first>ans.first) ans=res;
        else if(res.first==ans.first) ans.second+=res.second;
    }
    cout<<ans.first<<' '<<ans.second/2<<endl;

    return 0;
}