#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],n,cnt;
struct Node{
    int lc,rc;
    string op;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define op(x) tr[x].op

int f[N],ans[N];
void DFS(int x){
    if(!lc(x)&&!rc(x)){
        string s=op(x);
        s.erase(0,1);
        f[x]=a[atoi(s.c_str())];
        return ;
    }
    if(op(x)=="!"){
        DFS(lc(x));
        f[x]=!f[lc(x)];
    }else if(op(x)=="&"){
        DFS(lc(x));
        DFS(rc(x));
        f[x]=f[lc(x)]&&f[rc(x)];
    }else{
        DFS(lc(x));
        DFS(rc(x));
        f[x]=f[lc(x)]||f[rc(x)];
    }
}
void Assign(int x,int k){
    if(!lc(x)&&!rc(x)){
        string s=op(x);
        s.erase(0,1);
        ans[atoi(s.c_str())]=k;
        return ;
    }
    if(op(x)=="!") Assign(lc(x),k);
    else Assign(lc(x),k),Assign(rc(x),k);
}
void Solve(int x,int rev){
    if(!lc(x)&&!rc(x)){
        string s=op(x);
        s.erase(0,1);
        int k=atoi(s.c_str());
        ans[k]=(!a[k])^rev;
        return ;
    }
    if(op(x)=="!") Solve(lc(x),rev^1);
    else if(op(x)=="&"){
        if(!f[rc(x)]) Assign(lc(x),rev);
        else Solve(lc(x),rev);
        if(!f[lc(x)]) Assign(rc(x),rev);
        else Solve(rc(x),rev);
    }else{
        if(f[rc(x)]) Assign(lc(x),rev^1);
        else Solve(lc(x),rev);
        if(f[lc(x)]) Assign(rc(x),rev^1);
        else Solve(rc(x),rev);
    }
}

int main(){
    string s;
    getline(cin,s);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    vector<int> stk;
    s.push_back(' ');
    for(int i=0;i<s.size();i++){
        int pos=i;
        while(s[pos]!=' ') pos++;
        int x=++cnt;
        op(x)=s.substr(i,pos-i);
        if(op(x)=="&"||op(x)=="|"){
            lc(x)=stk.back();
            stk.pop_back();
            rc(x)=stk.back();
            stk.pop_back();
        }else if(op(x)=="!"){
            lc(x)=stk.back();
            stk.pop_back();
        }
        stk.push_back(x);
        i=pos;
    }
    DFS(stk.back());
    Solve(stk.back(),0);

    int q;
    cin>>q;
    while(q--){
        int pos;
        cin>>pos;
        cout<<ans[pos]<<endl;
    }

    return 0;
}