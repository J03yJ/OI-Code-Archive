#include<bits/stdc++.h>

using namespace std;

ifstream fin("trunk.in");
ofstream fout("trunk.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;
const int inf=1e9+7ll;

struct Node{
    int lc,rc,siz,dep,ans;
    pair<int,int> dat;
}tr[N<<3];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define dep(x) tr[x].dep
#define dat(x) tr[x].dat
#define ans(x) tr[x].ans

int cnt;
int NewAllc(pair<int,int> k){
    int x=++cnt;
    siz(x)=dep(x)=1;
    dat(x)=k;
    ans(x)=dat(x).second-1;
    return x;
}
void PushUp(int x){
    if(!lc(x)) siz(x)=dep(x)=1,ans(x)=dat(x).second-1;
    else{
        siz(x)=siz(lc(x))+siz(rc(x));
        dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
        dat(x)=dat(rc(x));
        ans(x)=max(ans(lc(x)),ans(rc(x))-siz(lc(x)));
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

void Insert(int x,pair<int,int> k){
    if(!lc(x)){
        lc(x)=NewAllc(min(dat(x),k));
        rc(x)=NewAllc(max(dat(x),k));
        return PushUp(x);
    }
    if(k<=dat(lc(x))) Insert(lc(x),k);
    else Insert(rc(x),k);
    Maintain(x);
}
void Erase(int x,pair<int,int> k,int fa=-1){
    if(!lc(x)){
        if(dat(lc(fa))==k) tr[fa]=tr[rc(fa)];
        else if(dat(rc(fa))==k) tr[fa]=tr[lc(fa)];
        return ;
    }
    if(k<=dat(lc(x))) Erase(lc(x),k,x);
    else Erase(rc(x),k,x);
    Maintain(x);
}

void Print(int x){
    if(!x) return ;
    Print(lc(x));
    cout<<x<<" : "<<lc(x)<<' '<<rc(x)<<' '<<dat(x).first<<'/'<<dat(x).second<<' '<<siz(x)<<' '<<dep(x)<<' '<<ans(x)<<endl;
    Print(rc(x));
}

int a[N],n,m;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    int root=NewAllc({inf,-inf});
    for(int i=1;i<=n;i++) Insert(root,{a[i],i});
    // Print(root);
    while(m--){
        int pos,x;
        cin>>pos>>x;
        Erase(root,{a[pos],pos});
        Insert(root,{a[pos]=x,pos});
        cout<<ans(root)+1<<endl;
        // Print(root);
    }

    return 0;
}