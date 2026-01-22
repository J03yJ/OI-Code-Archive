#include<bits/stdc++.h>

using namespace std;

ifstream fin("want.in");
ofstream fout("want.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e5+9;
const int p=998244353;

int c[N],n,a,b;

int H(int B){
    int res=0;
    for(int i=1;i<=n;i++) res=res*13331%B,res=(res+c[i])%B;
    return res;
}
pair<int,int> Hash(){
    return make_pair(H(1e9+7),H(p));
}
int cnt;
map<pair<int,int>,bool> vis;
void dfs(pair<int,int> k){
    // for(int i=1;i<=n;i++) cout<<c[i]<<' ';
    // cout<<endl;
    vis[k]=1;
    cnt++;
    reverse(c+1,c+a+1);
    pair<int,int> lc=Hash();
    if(!vis[lc]) dfs(lc);
    reverse(c+1,c+a+1);
    reverse(c+n-b+1,c+n+1);
    pair<int,int> rc=Hash();
    if(!vis[rc]) dfs(rc);
    reverse(c+n-b+1,c+n+1);
}

signed main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) c[i]=i;

    dfs(Hash());
    cout<<cnt<<endl;

    return 0;
}