#include<bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'

signed main(){
    int T;
    cin>>T;
    while(T--){
        int x,m,cnt=0;
        cin>>x>>m;
        for(int i=1;i<=x*2&&i<=m;i++){
            int z=i^x;
            if(z%i==0&&z%x) cnt++;
        }

        cnt+=m/x;
        for(int i=0;i<=100&&i<m/x;i++){
            int y=(m/x-i)*x^x;
            if(y>m) cnt--;
        }
        for(int i=1;i<=100;i++){
            int y=(m/x+i)*x^x;
            if(y<=m&&y) cnt++;
        }
        cout<<cnt<<endl;

        // int res=0;
        // for(int i=1;i<=m;i++){
        //     int z=i^x;
        //     if(z%i==0||z%x==0) res++;
        // }
        // cout<<res<<endl;
    }

    return 0;
}