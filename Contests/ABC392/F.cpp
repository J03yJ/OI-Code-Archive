#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=5e5+9;

struct Node{
    int lc,rc,siz;
}tr[N];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz

mt19937 rng(4649);
inline void PushUp(int x){siz(x)=siz(lc(x))+siz(rc(x))+1;}
inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    if(rng()&1){
        rc(x)=Merge(rc(x),y);
        return PushUp(x),x;
    }else{
        lc(y)=Merge(x,lc(y));
        return PushUp(y),y;
    }
}
inline pii Split(int x,int k){
    if(!x) return {0,0};
    if(k<=siz(lc(x))){
        pii res=Split(lc(x),k);
        lc(x)=sec(res);
        PushUp(x);
        return {fir(res),x};
    }else{
        pii res=Split(rc(x),k-siz(lc(x))-1);
        rc(x)=fir(res);
        PushUp(x);;
        return {x,sec(res)};
    }
}
inline void Print(int x){
    if(!x) return ;
    Print(lc(x));
    cout<<x<<' ';
    Print(rc(x));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int n;
    cin>>n;

    int root=0;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        siz(i)=1;
        pii res=Split(root,x-1);
        root=Merge(fir(res),Merge(i,sec(res)));
    }

    Print(root);cout<<endl;

    return 0;
}