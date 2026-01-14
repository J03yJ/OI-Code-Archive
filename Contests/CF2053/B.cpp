#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> vis(2*n+1,0),l(n+1,0),r(n+1,0),cnt(2*n+1,0);
        for(int i=1;i<=n;i++){
            cin>>l[i]>>r[i];
            if(l[i]==r[i]) vis[l[i]]=1,cnt[l[i]]++;
        }
        for(int i=1;i<=2*n;i++) vis[i]+=vis[i-1];

        for(int i=1;i<=n;i++){
            if(l[i]==r[i]){
                if(cnt[l[i]]==1) cout<<1;
                else cout<<0;
                continue ;
            }
            int cnt=vis[r[i]]-vis[l[i]-1];
            int len=r[i]-l[i]+1;
            if(cnt==len) cout<<0;
            else cout<<1;
        }
        cout<<'\n';
    }

    return 0;
}