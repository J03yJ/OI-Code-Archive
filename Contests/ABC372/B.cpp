#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> res;
    int x=0;
    while(n){
        if(n%3==1) res.push_back(x);
        else if(n%3==2) res.push_back(x),res.push_back(x);
        n/=3;
        x++;
    }
    cout<<res.size()<<endl;
    for(int x:res) cout<<x<<' ';cout<<endl;

    return 0;
}