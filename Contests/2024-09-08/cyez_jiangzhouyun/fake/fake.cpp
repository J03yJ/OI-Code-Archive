#include<bits/stdc++.h>
#include"fake.h"
using namespace std;

bool Check(int n,int m,int dx,int dy,int &lim){
    if(!lim) return 1;
    for(int i=1;i<=n;i+=dx){
        for(int j=1;j<=m;j+=dy){
            if(i==1&&j==1) continue ;
            lim--;
            if(!simons(dx,dy,1,1,i,j)) return 0;
            if(!lim) return 1;
        }
    }
    return 1;
}
int truth(int n,int m,int lim){
    int ans=0;
    map<pair<int,int>,int> mp;
    for(int i=n;i>=1;i--){
        if(n%i) continue ;
        for(int j=m;j>=1;j--){
            if(m%j) continue ;
            if(mp[{i,j}]) continue ;
            int f=Check(n,m,i,j,lim);
            ans+=f;
            if(!f){
                for(int x=1;x<=i;x++){
                    if(i%x) continue ;
                    for(int y=1;y<=j;y++){
                        if(j%y) continue ;
                        mp[{x,y}]=1;
                    }
                }
            }
        }
    }
    return ans;
}