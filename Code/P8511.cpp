#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

struct Node{
    int son[2],siz;
}tr[N<<6];
#define son(x,k) tr[x].son[k]
#define siz(x) tr[x].siz
#define int long long

int cnt;
int New(){return cnt++,siz(cnt)=son(cnt,0)=son(cnt,1)=0,cnt;}
int Build(){return cnt=0,New();}
void Modify(int x,int k,int flag){
    siz(x)+=flag;
    for(int i=60;~i;i--){
        if(!son(x,k>>i&1)) son(x,k>>i&1)=New();
        x=son(x,k>>i&1);
        siz(x)+=flag;
    }
}
int Query(int x,int k){
    int ans=0;
    if(!siz(x)) return ans;
    for(int i=60,f;~i;i--){
        f=k>>i&1;
        if(siz(son(x,f^1))){
            x=son(x,f^1);
            ans|=1ll<<i;
        }else{
            assert(siz(son(x,f)));
            x=son(x,f);
        }
    }
    return ans;
}

int a[N],fa[N],ans[N],n;
vector<int> son[N];
int Assign(int x,int k,int u,int v){
    int flag=x==u||x==v;
    for(int y:son[x]) flag|=Assign(y,k,u,v);
    if(!flag) ans[x]=k;
    return flag;
}

int res,root;
void DFS(int x){
    for(int y:son[x]) DFS(y);
    Modify(root,a[x],1);
    res=max(res,Query(root,a[x]));
}
void Work(int x,int pre){
    if(!x) return ;
    Work(fa[x],x);
    ans[x]=res;
    for(int y:son[x]) if(y!=pre) DFS(y);
    Modify(root,a[x],1);
    res=max(res,Query(root,a[x]));
}

signed main(){
    cin>>n;
    for(int i=2;i<=n;i++) cin>>fa[i],son[fa[i]].push_back(i);
    for(int i=1;i<=n;i++) cin>>a[i];

    int mx=-1,x=0,y=0;
    root=Build();
    for(int i=1;i<=n;i++){
        Modify(root,a[i],1);
        int tmp=Query(root,a[i]);
        if(tmp>mx) mx=tmp,x=i;
    }
    assert(x);
    for(int i=1;i<=x;i++){
        if(mx!=(a[i]^a[x])) continue ;
        y=i;
        break ;
    }
    assert(y);
    Assign(1,mx,x,y);

    root=Build(),res=0;
    Work(x,0);
    root=Build(),res=0;
    Work(y,0);

    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

    return 0;
}