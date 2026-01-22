#include<bits/stdc++.h>

using namespace std;

ifstream fin("song.in");
ofstream fout("song.out");
#define cin fin
#define cout fout

#define ssiz(x) (signed)x.size()
const int N=6e6+9;

int base[N],n,lim,cnt,root;
string s;
struct Node{
    int son[3],flip,val;
}tr[N];
#define son(x,k) tr[x].son[k]
#define flip(x) tr[x].flip
#define val(x) tr[x].val
void Push(int x){flip(x)^=1;}
void PushDown(int x){
    if(!flip(x)) return ;
    flip(son(x,0))^=1;
    flip(son(x,1))^=1;
    flip(son(x,2))^=1;
    swap(son(x,1),son(x,2));
    flip(x)=0;
}
void Build(int &x,int dep,int k){
    x=++cnt;
    if(dep==n) val(x)=k;
    else{
        Build(son(x,0),dep+1,k);
        Build(son(x,1),dep+1,k+base[dep]);
        Build(son(x,2),dep+1,k+base[dep]+base[dep]);
    }
}
void Next(int x,int dep){
    if(dep==n) return ;
    PushDown(x);
    swap(son(x,0),son(x,1));
    swap(son(x,1),son(x,2));
    Next(son(x,2),dep+1);
}
int r[N],ans[N];
void Print(int x,int dep,int k){
    PushDown(x);
    if(dep==n) r[k]=val(x);
    else{
        Print(son(x,0),dep+1,k);
        Print(son(x,1),dep+1,k+base[dep]);
        Print(son(x,2),dep+1,k+base[dep]+base[dep]);
    }
}

int main(){
    cin>>n>>s;
    base[0]=1;for(int i=1;i<=n;i++) base[i]=base[i-1]*3;
    lim=base[n];

    Build(root,0,0);
    for(auto op:s){
        if(op=='0') Push(root);
        else Next(root,0);
    }
    Print(root,0,0);
    for(int i=0;i<lim;i++) ans[r[i]]=i;
    for(int i=0;i<lim;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}