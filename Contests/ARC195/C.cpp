#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;

inline void Solve(){
    int r,b;
    cin>>r>>b;
    if(r&1) return cout<<"No"<<endl,void();
    if((b&1)&&!r) return cout<<"No"<<endl,void();
    cout<<"Yes"<<endl;
    vector<array<int,3>> ans;
    int tmp=r+b+1;
    if(~b&1){
        int x=0,y=0;
        if(b){
            ans.push_back({1,x,y});
            for(int i=1;i<(b>>1);i++){
                x--,y++;
                ans.push_back({1,x,y});
            }
            x++,y++;
            ans.push_back({1,x,y});
            for(int i=1;i<(b>>1);i++){
                x++,y--;
                ans.push_back({1,x,y});
            }
            x++,y--;
        }
        if(r){
            ans.push_back({0,x,y});
            for(int i=1;i<(r>>1);i++){
                y--;
                ans.push_back({0,x,y});
            }
            x--;
            ans.push_back({0,x,y});
            for(int i=1;i<(r>>1);i++){
                y++;
                ans.push_back({0,x,y});
            }
        }
    }else if(b>1){
        int x=0,y=0;
        b-=3,r-=2;
        ans.push_back({1,x,y});
        x++,y--;
        ans.push_back({0,x,y});
        y++;
        ans.push_back({1,x,y});
        x--,y--;
        ans.push_back({1,x,y});
        if(b){
            for(int i=0;i<(b>>1);i++){
                x--,y--;
                ans.push_back({1,x,y});
            }
            x--,y++;
            ans.push_back({1,x,y});
            for(int i=1;i<(b>>1);i++){
                x++,y++;
                ans.push_back({1,x,y});
            }
            x++,y++;
        }else x--,y++;
        ans.push_back({0,x,y});
        if(r){
            for(int i=0;i<(r>>1);i++){
                y++;
                ans.push_back({0,x,y});
            }
            x++;
            ans.push_back({0,x,y});
            for(int i=1;i<(r>>1);i++){
                y--;
                ans.push_back({0,x,y});
            }
        }
    }else{
        int x=0,y=0;
        ans.push_back({1,x,y});
        x--,y++;
        ans.push_back({0,x,y});
        for(int i=1;i<(r>>1);i++){
            y++;
            ans.push_back({0,x,y});
        }
        x++;
        ans.push_back({0,x,y});
        for(int i=1;i<(r>>1);i++){
            y--;
            ans.push_back({0,x,y});
        }
    }
    for(auto t:ans){
        if(t[0]) cout<<'B'<<' '<<t[1]+tmp<<' '<<t[2]+tmp<<endl;
        else cout<<'R'<<' '<<t[1]+tmp<<' '<<t[2]+tmp<<endl;
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}