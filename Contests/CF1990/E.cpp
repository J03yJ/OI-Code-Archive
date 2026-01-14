#include<bits/stdc++.h>

using namespace std;

const int N=5e3+9;

int n,cnt;
int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int dis[N],fa[N],siz[N],dfn[N],dcnt;
vector<int> a[N];
void dfs(int x){
    dis[x]=0;
    siz[x]=1;
    dfn[x]=++dcnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        dfs(y);
        siz[x]+=siz[y];
        dis[x]=max(dis[x],dis[y]+1);
    }
    a[dis[x]].push_back(x);
}
int cntf=0;
void calc_siz(int x){
    if(dis[x]<cntf){
        siz[x]=0;
        return ;
    }
    siz[x]=1;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        calc_siz(y);
        siz[x]+=siz[y];
    }
}

void clear(){
    for(int i=1;i<=n;i++) fi[i]=0,a[i].clear();
    for(int i=1;i<=adj;i++) to[i]=ne[i]=0;
    adj=dcnt=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            adeg(x,y);
            adeg(y,x);
        }
        cnt=200;
        cntf=0;
        fa[1]=1;
        dfs(1);
        int root=1;
        while(cnt){
            int mx=0,pos=0,edp=0;
            for(int i=1;i<=n;i++){
                if(dis[i]<cntf) continue ;
                if(dfn[i]<dfn[root]||dfn[i]>=dfn[root]+siz[root]){
                    edp=i;
                    continue ;
                }
                int e=min(siz[i],siz[root]-siz[i]);
                if(e>mx) mx=e,pos=i;
            }
            if(edp&&a[dis[cntf]].size()+siz[root]-siz[fa[root]]>mx){
                pos=edp;
                cout<<"? "<<edp<<endl;
            }else cout<<"? "<<pos<<endl;
            cout.flush();
            int res=0;
            cin>>res;
            if(res) root=pos;
            else{
                cntf++;
                if(root!=1) root=fa[root];
                calc_siz(root);
            }
            if(dis[root]==cntf){
                cout<<"! "<<root<<endl;
                cout.flush();
                break ;
            }
            cnt--;
            if(!cnt){
                cout<<"! "<<root<<endl;
                cout.flush();
                break ;
            }
        }
        clear();
    }
}