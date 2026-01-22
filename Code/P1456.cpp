#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

namespace meap{
    struct node{
        int lc,rc,dat;
        node(){};
        node(int l,int r,int d){
            lc=l;rc=r;dat=d;
        }
    }tr[N<<2];
    int cnt;
    int merge(int x,int y){
        if(!x||!y) return x|y;
        if(tr[x].dat<tr[y].dat) swap(x,y);
        if(rand()%2) swap(tr[x].lc,tr[x].rc);
        tr[x].lc=merge(tr[x].lc,y);
        return x;
    }

    struct meap{
        int root;
        meap(){};
        meap(int val){
            tr[++cnt]=node(0,0,val);
            root=cnt;
        }
        void join(meap y){root=merge(root,y.root);}
        void pop(){root=merge(tr[root].lc,tr[root].rc);}
        int top(){return tr[root].dat;}
    };
}
namespace dsu{
    int fa[N];
    int find(int x){
        if(fa[x]==x) return x;
        else return fa[x]=find(fa[x]);
    }
    void merge(int x,int y){fa[find(y)]=find(x);}
}

meap::meap h[N];

int main(){
    int n;
    while(cin>>n){
        for(int i=1,x;i<=n;i++) cin>>x,h[i]=meap::meap(x);
        for(int i=1;i<=n;i++) dsu::fa[i]=i;
        int m;
        cin>>m;
        while(m--){
            int x,y;
            cin>>x>>y;
            x=dsu::find(x);
            y=dsu::find(y);
            if(x==y){
                cout<<-1<<endl;
                continue ;
            }
            dsu::merge(x,y);
            int a=h[x].top();h[x].pop();h[x].join(meap::meap(a/2));
            int b=h[y].top();h[y].pop();h[y].join(meap::meap(b/2));
            h[x].join(h[y]);
            cout<<h[x].top()<<endl;
        }
        memset(meap::tr,0,sizeof(meap::tr));
    }
}