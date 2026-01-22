#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
const double eps=1e-4;

int n,m,s,k;
struct edge{
    int u,v,w;
    bool operator <(edge e){
        return w<e.w;
    }
};

int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fa[find(y)]=find(x);
}

int check(double val,vector<edge> &e1,vector<edge> &e2){
    vector<pair<edge,int>> e;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=0,j=0;i<e1.size()||j<e2.size();){
        if(i>=e1.size()) e.push_back({e2[j++],0});
        else if(j>=e2.size()) e.push_back({e1[i++],1});
        else if(e1[i].w+val<e2[j].w) e.push_back({e1[i++],1});
        else e.push_back({e2[j++],0});
    }
    int tot=0,cnt=0;
    for(int i=0;i<e.size()&&tot<n-1;i++){
        int x=e[i].first.u,y=e[i].first.v;
        if(find(x)==find(y)) continue ;
        if(e[i].second) cnt++;
        tot++;
        merge(x,y);
    }
    return cnt;
}
double solve(double val,vector<edge> &e1,vector<edge> &e2){
    vector<pair<edge,int>> e;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=0,j=0;i<e1.size()||j<e2.size();){
        if(i>=e1.size()) e.push_back({e2[j++],0});
        else if(j>=e2.size()) e.push_back({e1[i++],1});
        else if(e1[i].w+val<e2[j].w) e.push_back({e1[i++],1});
        else e.push_back({e2[j++],0});
    }
    int tot=0,cnt=0;
    double ans=0;
    for(int i=0;i<e.size()&&tot<n-1;i++){
        int x=e[i].first.u,y=e[i].first.v;
        if(find(x)==find(y)) continue ;
        if(cnt==k&&e[i].second) continue ;
        if(e[i].second) cnt++;
        ans+=e[i].first.w+val*e[i].second;
        tot++;
        merge(x,y);
    }
    return ans;
}

int main(){
    cin>>n>>m>>s>>k;
    vector<edge> e1,e2;
    for(int i=1;i<=m;i++){
        edge e;
        cin>>e.u>>e.v>>e.w;
        if(e.u==e.v) continue ;
        if(e.u==s||e.v==s) e1.push_back(e);
        else e2.push_back(e);
    }
    sort(e1.begin(),e1.end());
    sort(e2.begin(),e2.end());

    if(e1.size()<k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    if(check(-1e6,e1,e2)<k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    if(solve(-1e6,e1,e2)==-1){
        cout<<"Impossible"<<endl;
        return 0;
    }
    double l=-1e6,r=1e6;
    while(r-l>eps){
        double mid=(l+r)/2;
        if(check(mid,e1,e2)>k) l=mid;
        else r=mid;
    }
    cout<<(int)round(solve(l,e1,e2)-k*l)<<endl;
    return 0;
}