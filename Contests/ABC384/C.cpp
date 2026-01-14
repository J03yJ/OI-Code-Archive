#include<bits/stdc++.h>

using namespace std;

int a[5];

int main(){
    for(int i:{0,1,2,3,4}) cin>>a[i];

    vector<pair<int,string>> v;
    for(int sta=0;sta<32;sta++){
        string s;
        int sum=0;
        for(int i=0;i<5;i++){
            if(sta>>i&1){
                sum+=a[i];
                s.push_back('A'+i);
            }
        }
        v.push_back({sum,s});
    }
    sort(v.begin(),v.end(),[](auto x,auto y){
        if(x.first!=y.first) return x.first>y.first;
        else return x<y;
    });
    v.pop_back();

    for(auto p:v) cout<<p.second<<endl;

    return 0;
}