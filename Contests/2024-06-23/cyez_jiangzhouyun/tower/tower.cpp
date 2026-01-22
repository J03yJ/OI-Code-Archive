#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
#define int long long

int a[N],b[N],pre[N];

signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int j=1;j<=n;j++) cin>>b[j];
    while(m--){
        int s,t,u;
        cin>>s>>t>>u;
        if(s==t){
            cout<<0<<endl;
            continue ;
        }
        int Lst=u,Cur=0,Tot=0,Cst=0;
        priority_queue<tuple<int,int,int>> q;
        for(int i=s;i<t;i++){
            
        }
    }
}