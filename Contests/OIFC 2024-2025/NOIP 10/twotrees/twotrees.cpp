#include<bits/stdc++.h>

using namespace std;

ifstream fin("twotrees.in");
ofstream fout("twotrees.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()
const int N=5e5+9;

struct Tree{
    int fi[N],ne[N<<1],to[N<<1],adj;
    void AdEg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    int fa[N],dep[N],siz[N],hson[N];
    void DFS1(int x){
        siz[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x]) continue ;
            fa[y]=x;
            dep[y]=dep[x]+1;
            DFS1(y);
            siz[x]+=siz[y];
            if(siz[y]>siz[hson[x]]) hson[x]=y;
        }
    }
    int top[N],dfn[N],idfn[N],dcnt;
    void DFS2(int x,int t){
        top[x]=t;
        dfn[x]=++dcnt;
        idfn[dcnt]=x;
        if(hson[x]) DFS2(hson[x],t);
        else return ;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x]) continue ;
            if(y==hson[x]) continue ;
            DFS2(y,y);
        }
    }
    int LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
    vector<int> Pth(int x,int y){
        vector<int> a,b;
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]]){
                a.push_back(dfn[x]);
                a.push_back(dfn[top[x]]);
                x=fa[top[x]];
            }else{
                b.push_back(dfn[y]);
                b.push_back(dfn[top[y]]);
                y=fa[top[y]];
            }
        }
        a.push_back(dfn[x]);
        a.push_back(dfn[y]);
        while(b.size()) a.push_back(b.back()),b.pop_back();
        return a;
    }
}t1,t2;

int w[N],n,m;
vector<array<int,5>> qr[2][N<<1];
vector<array<int,4>> nowq[N];
vector<int> pt[2][N<<1];
vector<pair<int,int>> nowp[N];
long long tr[N],ans[N];
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
long long Ask(int x){
    long long ans=0;
    while(x){
        ans+=tr[x];
        x&=x-1;
    }
    return ans;
}
long long Ask(int l,int r){
    return Ask(r)-Ask(l-1);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        t1.AdEg(u,v),t1.AdEg(v,u);
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        t2.AdEg(u,v),t2.AdEg(v,u);
    }

    t1.DFS1(1),t1.DFS2(1,1);
    t2.DFS1(1),t2.DFS2(1,1);
    for(int i=1;i<=n;i++){
        pt[0][t1.dfn[i]-t2.dfn[i]+N].push_back(i);
        pt[1][t1.dfn[i]+t2.dfn[i]].push_back(i);
    }
    for(int t=1,u,v,p,q;t<=m;t++){
        cin>>u>>v>>p>>q;
        vector<int> a=t1.Pth(u,v),b=t2.Pth(p,q);
        vector<int> ac(ssiz(a)>>1),bc(ssiz(b)>>1);
        for(int i=0;i<ssiz(ac);i++) ac[i]=a[i<<1|1]-a[i<<1];
        for(int i=0;i<ssiz(bc);i++) bc[i]=b[i<<1|1]-b[i<<1];
        for(int i=0,j=0,si=0,sj=0;i<ssiz(ac)&&j<ssiz(bc);){
            int tmp=min(abs(ac[i])-si,abs(bc[j])-sj);
            int fa=ac[i]>=0?1:-1,fb=bc[j]>=0?1:-1;
            int la=a[i<<1]+fa*si,ra=la+fa*tmp;
            int lb=b[j<<1]+fb*sj,rb=lb+fb*tmp;
            if(la>ra) swap(la,ra);
            if(lb>rb) swap(lb,rb);
            if(fa*fb==1){
                qr[0][(a[i<<1]+fa*si)-(b[j<<1]+fb*sj)+N].push_back({la,ra,lb,rb,t});
            }else{
                qr[1][(a[i<<1]+fa*si)+(b[j<<1]+fb*sj)].push_back({la,ra,lb,rb,t});
            }
            si+=tmp+1,sj+=tmp+1;
            if(si>ac[i]*fa) si=0,i++;
            if(sj>bc[j]*fb) sj=0,j++;
        }
    }

    for(int k:{0,1}){
        for(int val=0;val<N+N;val++){
            if(!ssiz(qr[k][val])) continue ;
            vector<int> tim;
            for(auto t:qr[k][val]){
                tim.push_back(t[0]-1);
                nowq[t[0]-1].push_back({t[2],t[3],-1,t[4]});
                tim.push_back(t[1]);
                nowq[t[1]].push_back({t[2],t[3],1,t[4]});
            }
            for(int x:pt[k][val]){
                tim.push_back(t1.dfn[x]);
                nowp[t1.dfn[x]].push_back({t2.dfn[x],w[x]});
            }
            sort(tim.begin(),tim.end());
            tim.erase(unique(tim.begin(),tim.end()),tim.end());
            for(int tk:tim){
                for(auto p:nowp[tk]) Add(p.first,p.second);
                for(auto q:nowq[tk]) ans[q[3]]+=q[2]*Ask(q[0],q[1]);
                nowp[tk].clear(),nowq[tk].clear();
            }
            for(int x:pt[k][val]) Add(t2.dfn[x],-w[x]);
        }
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}