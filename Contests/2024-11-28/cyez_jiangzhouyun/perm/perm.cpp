#include<bits/stdc++.h>

using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");
#define cin fin
#define cout fout

const int N=3e5+9;

int p[N],vis[N],n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    
    int res=0;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        int cnt=0,cur=i;
        while(!vis[cur]){
            vis[cur]=1;
            cur=p[cur];
            cnt++;
        }
        res+=max(cnt-1,1);
    }
    cout<<res<<endl;

    return 0;
}