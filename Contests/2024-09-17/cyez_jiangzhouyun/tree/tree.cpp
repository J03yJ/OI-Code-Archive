#include<bits/stdc++.h>

using namespace std;

ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int siz[N],ans;
void DFS(int x){
    siz[x]=1;
    int cnt=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        DFS(y);
        siz[x]+=siz[y];
        cnt+=siz[y]*siz[y];
    }
    cnt=siz[x]*siz[x]-cnt-1;
    cnt=cnt/2+1;
    if(cnt&1) ans^=x;
}
int Solve(int n,int s){
    ans=0;
    for(int i=2;i<=n;i++){
        int fa=max(1ll,i-(i&-i)*s);
        AdEg(fa,i);
    }
    DFS(1);
    
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
    return ans;
}
int F1(int n){
    if(n==1) return 1;
    int k=(n-2)%8;
    if(k==0||k==1) return 2;
    if(k==4||k==5) return 0;
    if(k==2||k==3) return n-(k-2)+3;
    return n-(k-6)+1;
}
int F3(int n){
    if(n==1) return 1;
    if(n==2) return 2;
    if(n==3) return 1;
    int k=(n-2)%8;
    if(k==0) return n+1;
    if(k==1) return n-2;
    if(k==2) return 4;
    if(k==3) return 2;
    if(k==4) return n-1;
    if(k==5) return n;
    if(k==6) return (n&-n)-1<<1;
    if(k==7) return 0;
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,s;
        cin>>n>>s;
        if(s==1) cout<<F1(n)<<endl;
        else if(s==3) cout<<F3(n)<<endl;
        else cout<<Solve(n,2)<<endl;
    }
    return 0;
}