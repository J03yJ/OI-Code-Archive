#include<bits/stdc++.h>

using namespace std;

int main(){
    int n,l,r;
    cin>>n>>l>>r;
    map<int,int> mp;
    while(n--){
        int x,k;
        cin>>x>>k;
        mp[x]=k;
    }
    while(true){
        int pos=1e9;
        for(int i=l;i<=r;i++){
            if(mp[i]>1){
                pos=i;
                break ;
            }
        }
        if(pos==1e9) break ;
        mp[pos-1]++;
        mp[pos+1]++;
        mp[pos]-=2;
        for(int i=l;i<=r;i++) cout<<mp[i]<<' ';cout<<endl;
    }

    for(int i=l;i<=r;i++) cout<<i<<" : "<<mp[i]<<endl;

    return 0;
}