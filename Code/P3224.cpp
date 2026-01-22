#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],ra[N],n;

struct node{
    int lc,rc,siz;
    node(){}
    node(int Lc,int Rc,int Siz){
        lc=Lc,rc=Rc,siz=Siz;
    }
}tr[N*24];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz

int cnt=0;vector<int> Trs;

int Add(){
    int x=0;
    if(Trs.size()) x=Trs.back(),Trs.pop_back();
    else x=++cnt;
    // cout<<cnt<<endl;
    return x;
}
void Del(int pos){
    tr[pos]=node(0,0,0);
    Trs.push_back(pos);
}

void insert(int &x,int L,int R,int k){
    if(!x) x=Add();
    if(L==R){
        siz(x)++;
        // cout<<"["<<x<<"] := "<<L<<endl;
        return ;
    }
    int mid=L+R>>1;
    if(k<=mid) insert(lc(x),L,mid,k);
    else insert(rc(x),mid+1,R,k);
    siz(x)=siz(lc(x))+siz(rc(x));
    // cout<<"["<<x<<"] "<<siz(x)<<' '<<siz(lc(x))<<' '<<siz(rc(x))<<' '<<L<<' '<<R<<endl;
}
void erase(int x){
    if(!x) return ;
    erase(lc(x));erase(rc(x));
    Del(x);
    // cout<<"~["<<x<<"]"<<endl;
}
void get_node(int x,int L,int R,vector<int> &v){
    if(!x) return ;
    if(L==R){
        v.push_back(L);
        return ;
    }
    int mid=L+R>>1;
    get_node(lc(x),L,mid,v);get_node(rc(x),mid+1,R,v);
}
int merge(int x,int y){
    if(siz(x)<siz(y)) swap(x,y);
    vector<int> v;
    get_node(y,1,n,v);
    // cout<<cnt<<' '<<Trs.size()<<endl;
    erase(y);
    // cout<<cnt<<' '<<Trs.size()<<endl;
    for(int val:v) insert(x,1,n,val);
    // cout<<cnt<<' '<<Trs.size()<<endl;
    // cout<<endl;
    return x;
}
int query(int x,int L,int R,int k){
    if(siz(x)<k) return -1;
    if(L==R) return L;
    int mid=L+R>>1;
    // cout<<L<<' '<<R<<' '<<siz(x)<<' '<<siz(lc(x))<<' '<<siz(rc(x))<<' '<<k<<endl;
    if(siz(lc(x))>=k) return query(lc(x),L,mid,k);
    else return query(rc(x),mid+1,R,k-siz(lc(x))); 
}

int fa[N];
int Find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){
    fa[Find(y)]=Find(x);
}

int root[N];

int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        fa[i]=i;
        insert(root[i],1,n,a[i]);
        ra[a[i]]=i;
        // cout<<cnt<<endl;
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        x=Find(x),y=Find(y);
        if(x==y) continue ;
        Merge(x,y);
        root[Find(x)]=merge(root[x],root[y]);
    }
    int q;
    cin>>q;
    while(q--){
        char c;
        int x,y;
        cin>>c>>x>>y;
        if(c=='B'){
            x=Find(x),y=Find(y);
            if(x==y) continue ;
            Merge(x,y);
            root[Find(x)]=merge(root[x],root[y]);
        }else{
            int k=query(root[Find(x)],1,n,y);
            if(~k) cout<<ra[k]<<endl;
            else cout<<-1<<endl;
        }
    }
}