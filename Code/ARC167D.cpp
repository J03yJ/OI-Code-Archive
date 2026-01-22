#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int p[N],pos[N];
int fa[N],siz[N],mn[N];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
set<pair<int,int>> s;
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return ;
    s.erase({mn[x],x});s.erase({mn[y],y});
    fa[y]=x;siz[x]+=siz[y];mn[x]=min(mn[x],mn[y]);
    s.insert({mn[x],x});
}

int main(){
    int T;
    cin>>T;
    while(T--){
        s.clear();
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>p[i],pos[p[i]]=i;
        for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,mn[i]=i,s.insert({i,i});
        for(int i=1;i<=n;i++) merge(p[i],i);
        for(int i=1;i<=n;i++){
            if(s.size()==1) break ;
            auto it=s.begin();
            while(find(it->second)==find(i)) it++;
            int x=it->first;
            if(x<p[i]||siz[find(i)]==1){
                int j=pos[x];
                swap(p[i],p[j]);
                swap(pos[p[i]],pos[p[j]]);
                merge(j,i);
            }
            siz[find(i)]--;
        }
        for(int i=1;i<=n;i++) cout<<p[i]<<' ';cout<<endl;
    }
    return 0;
}