#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int &x:a) cin>>x;
        sort(a.begin(),a.end());

        bool flag=0;
        map<int,int> mp;
        for(int x:a) mp[x]++;
        for(int x:a){
            if(!mp[x]) continue ;
            if(mp[x]<2) continue ;
            if(mp[x]>=4){
                flag=1;
                break ;
            }
            int y=x+1;
            while(mp[y]){
                if(mp[y]>=2){
                    flag=1;
                    break ;
                }
                mp[y]=0;
                y++;
            }
            if(flag) break ;
        }

        if(flag) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }

    return 0;
}