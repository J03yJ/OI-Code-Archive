#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj,n,pos;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N],dep[N],mx[N],mx2[N];
void DFS(int x){
    mx[x]=dep[x],mx2[x]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        DFS(y);
        if(mx[y]>mx[x]) mx2[x]=mx[x],mx[x]=mx[y];
        else if(mx[y]>mx2[x]) mx2[x]=mx[y];
    }
}
void Clear(){
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            AdEg(u,v);
            AdEg(v,u);
        }
        cin>>pos>>pos;

        fa[1]=0;
        DFS(1);
        vector<int> p;
        int cur=pos;
        while(cur){
            p.push_back(cur);
            cur=fa[cur];
        }
        reverse(p.begin(),p.end());

        int mid=p.size()+1>>1,flag=0;
        p.push_back(pos);
        for(int i=0;i<mid;i++){
            int x=p[i],disa=dep[x],disb=0;
            for(int j=fi[x];j;j=ne[j]){
                int y=to[j];
                if(y==fa[x]) continue ;
                if(y==p[i+1]) continue ;
                disa=max(disa,mx[y]);
            }

            int y=p[i+1];
            for(int j=fi[y];j;j=ne[j]){
                int z=to[j];
                if(z==fa[y]) continue ;
                if(z==p[i+2]) continue ;
                disb=max(disb,mx[z]);
            }
            disb+=dep[pos]-dep[y];

            if(disa>disb){
                flag=1;
                break ;
            }
        }
        if(flag) cout<<"Alice"<<endl;
        else cout<<"Bob"<<endl;

        Clear();
    }
    return 0;
}