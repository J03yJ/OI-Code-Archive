#include<bits/stdc++.h>

using namespace std;

#define Allc(x) x.begin(),x.end()
const int N=1e6+9;
const int inf=1e9;

struct Node{
    int lc,rc,siz,dep,mx;
    array<int,3> dat;
}tr[N<<3];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define dep(x) tr[x].dep
#define dat(x) tr[x].dat
#define mx(x) tr[x].mx

int cnt;
int NewAllc(array<int,3> k){
    int x=++cnt;
    siz(x)=k[2]-k[1]+1;
    dep(x)=1;
    dat(x)=k;
    return x;
}
void PushUp(int x){
    if(!lc(x)) dep(x)=1,siz(x)=dat(x)[2]-dat(x)[1]+1;
    else{
        siz(x)=siz(lc(x))+siz(rc(x));
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        dat(x)=max(dat(lc(x)),dat(rc(x)));
    }
}
void Rotate(int x,int flag){
    if(!flag){
        int y=lc(x);
        lc(x)=lc(y);
        lc(y)=rc(y);
        rc(y)=rc(x);
        rc(x)=y;
        PushUp(y);
    }else{
        int y=rc(x);
        rc(x)=rc(y);
        rc(y)=lc(y);
        lc(y)=lc(x);
        lc(x)=y;
        PushUp(y);
    }
    PushUp(x);
}
void Maintain(int x){
    if(dep(lc(x))>dep(rc(x))+1){
        if(dep(lc(lc(x)))==dep(rc(x))) Rotate(lc(x),1);
        Rotate(x,0);
    }else if(dep(rc(x))>dep(lc(x))+1){
        if(dep(rc(rc(x)))==dep(lc(x))) Rotate(rc(x),0);
        Rotate(x,1);
    }else PushUp(x);
}

void Insert(int x,array<int,3> k){
    if(!lc(x)){
        lc(x)=NewAllc(min(dat(x),k));
        rc(x)=NewAllc(max(dat(x),k));
        return PushUp(x);
    }
    if(k<=dat(lc(x))) Insert(lc(x),k);
    else Insert(rc(x),k);
    Maintain(x);
}
void Erase(int x,array<int,3> k,int fa=-1){
    if(!lc(x)){
        if(dat(lc(fa))==k) tr[fa]=tr[rc(fa)];
        else if(dat(rc(fa))==k) tr[fa]=tr[lc(fa)];
        else assert(0);
        return ;
    }
    if(k<=dat(lc(x))) Erase(lc(x),k,x);
    else Erase(rc(x),k,x);
    Maintain(x);
}
pair<array<int,3>,int> Rank(int x,int k){
    if(!lc(x)) return {dat(x),k};
    if(k<=siz(lc(x))) return Rank(lc(x),k);
    else return Rank(rc(x),k-siz(lc(x)));
}

int a[N],nxt[N],ans[N],n,q;
vector<pair<int,int>> qry[N];
void Print(int x){
    if(!x) return ;
    Print(lc(x));
    if(!lc(x)) for(int i=dat(x)[1];i<=dat(x)[2];i++) cout<<a[i]<<' ';
    Print(rc(x));
}
void Pr(int x){
    if(!x) return ;
    Pr(lc(x));
    if(!lc(x)) for(int i=dat(x)[1];i<=dat(x)[2];i++) cout<<dat(x)[0]<<' ';
    Pr(rc(x));
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,t,x;i<=q;i++){
        cin>>t>>x;
        t=min(t,n);
        qry[t].push_back({i,x});
    }

    a[n+1]=inf;
    vector<int> stk;
    stk.push_back(n+1);
    for(int i=n;i;i--){
        while(stk.size()&&a[stk.back()]<a[i]) stk.pop_back();
        nxt[i]=stk.back();
        stk.push_back(i);
    }
    reverse(Allc(stk));

    int root=NewAllc({inf,n+1,n+1});
    for(int i=1;i<=n;i=nxt[i]) Insert(root,{a[i],i,nxt[i]-1});
    for(int i=0;i<=n;i++){
        for(pair<int,int> p:qry[i]){
            auto x=Rank(root,p.second);
            ans[p.first]=a[x.first[1]+x.second-1];
        }
        auto x=Rank(root,n/2);
        int pos=x.first[1]+x.second-1;
        if(pos==x.first[2]) continue ;
        Erase(root,x.first);
        Insert(root,{x.first[0],x.first[1],pos});
        // cout<<x.first[0]<<' '<<x.first[1]<<' '<<x.first[2]<<' '<<x.second<<' '<<pos+1<<endl;
        for(int j=pos+1;j<=x.first[2];j=nxt[j]) Insert(root,{a[j],j,min(nxt[j]-1,x.first[2])});
        // Print(root);cout<<endl;
        // Pr(root);cout<<endl;
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    return 0;
}