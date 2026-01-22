#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=1e6+9;
bool vis[N];

signed main(){
    int n;
    cin>>n;
    int b=sqrt(n),c=0;
    while(c*c*c<=n) c++;
    c--;
    int cnt=0,ans=0;
    for(int i=1;i<=c;i++){
        if(vis[i]) continue ;
        if(i==1){
            ans++;
            vis[i]=1;
            continue  ;
        }
        int x=i;
        while(true){
            if(x<=c) vis[x]=1;
            else if(x<=b) cnt++;
            if(x!=i) ans++;
            if(x>n/i) break ;
            else x*=i;
        }
    }
    cout<<ans+(b-c-cnt)<<endl;
}