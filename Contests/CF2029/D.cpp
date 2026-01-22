#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=2e5+9;

int d[N],n,m;
unordered_set<int> s[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1,u,v;i<=m;i++){
            cin>>u>>v;
            s[u].insert(v);
            s[v].insert(u);
            d[u]++,d[v]++;
        }
        queue<int> q;
        for(int i=1;i<=n;i++) q.push(i);
        vector<array<int,3>> ans;
        while(q.size()){
            int x=q.front();
            q.pop();
            if(d[x]<=1) continue ;
            int u=*s[x].begin();
            s[x].erase(u);
            s[u].erase(x);
            int v=*s[x].begin();
            s[x].erase(v);
            s[v].erase(x);
            d[x]-=2,d[u]--,d[v]--;
            ans.push_back({x,u,v});
            if(s[u].find(v)!=s[u].end()){
                s[u].erase(v);
                s[v].erase(u);
                d[u]--,d[v]--;
            }else{
                s[u].insert(v);
                s[v].insert(u);
                d[u]++,d[v]++;
            }
            if(d[u]>1) q.push(u);
            if(d[v]>1) q.push(v);
            if(d[x]>1) q.push(x);
        }
        vector<pair<int,int>> e;
        for(int i=1;i<=n;i++){
            if(ssiz(s[i])==1){
                if(*s[i].begin()<i) e.push_back({i,*s[i].begin()});
            }
        }
        if(ssiz(e)){
            while(ssiz(e)>1){
                int x=e.back().first,y=e.back().second;
                e.pop_back();
                ans.push_back({e.back().first,x,y});
            }
            for(int i=1;i<=n;i++){
                if(!ssiz(s[i])){
                    int x=e.back().first,y=e.back().second;
                    e.pop_back();
                    e.push_back({i,x});
                    e.push_back({i,y});
                    ans.push_back({i,x,y});
                }
            }
        }
        if(ssiz(ans)>2*max(n,m)) assert(0);
        cout<<ssiz(ans)<<endl;
        for(auto t:ans) cout<<t[0]<<' '<<t[1]<<' '<<t[2]<<endl;
        for(int i=1;i<=n;i++) s[i].clear(),d[i]=0;
    }

    return 0;
}