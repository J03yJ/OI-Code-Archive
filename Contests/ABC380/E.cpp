#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int c[N],ans[N],fa[N],l[N],r[N],n,q;
int Find(int x){
    if(x==fa[x]) return x;
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){
    x=Find(x),y=Find(y);
    fa[Find(y)]=Find(x);
    l[x]=min(l[x],l[y]);
    r[x]=max(r[x],r[y]);
}

int main(){
    cin>>n>>q;
    iota(c+1,c+n+1,1);
    iota(fa+1,fa+n+1,1);
    iota(l+1,l+n+1,1);
    iota(r+1,r+n+1,1);
    for(int i=1;i<=n;i++) ans[i]=1;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;
            x=Find(x);
            ans[c[x]]-=r[x]-l[x]+1;
            c[x]=y;
            ans[c[x]]+=r[x]-l[x]+1;
            if(l[x]!=1&&c[x]==c[Find(l[x]-1)]) Merge(x,l[x]-1);
            if(r[x]!=n&&c[x]==c[Find(r[x]+1)]) Merge(x,r[x]+1);
        }else if(op==2){
            int x;
            cin>>x;
            cout<<ans[x]<<endl;
        }
    }

    return 0;
}