#include<bits/stdc++.h>

using namespace std;

const int N=2e6+9;

int fi[N],ne[N<<1],to[N<<1],adj,n;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
void ClearA(){
    for(int i=1;i<=n;i++) fi[i]=0;
    adj=0;
}

int vis[N],cnt0,cnt1,cntu,cntnl;
char c[N];
void DFS(int x){
    vis[x]=1;
    bool flag=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        flag=1;
        DFS(y);
    }
    if(!flag){
        if(c[x]=='0') cnt0++;
        else if(c[x]=='1') cnt1++;
        else cntu++;
    }else if(c[x]=='?') cntnl++;
    vis[x]=0;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            AdEg(u,v);
            AdEg(v,u);
        }
        for(int i=1;i<=n;i++) cin>>c[i];

        cnt0=cnt1=cntu=cntnl=0;
        DFS(1);
        if(c[1]!='?'){
            if(c[1]=='0') cout<<cnt1+(cntu+1)/2<<endl;
            else cout<<cnt0+(cntu+1)/2<<endl;
        }else{
            cntnl--;
            if(cnt0==cnt1&&cntnl%2) cout<<max(cnt1,cnt0)+(cntu+1)/2<<endl; 
            else cout<<max(cnt1,cnt0)+cntu/2<<endl;
        }

        ClearA();
    }

    return 0;
}