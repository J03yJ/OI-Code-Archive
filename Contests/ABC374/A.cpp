#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin>>s;
    if(s.size()>=3){
        if(s.substr(s.size()-3,3)=="san") cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }else cout<<"No"<<endl;
    
    return 0;
}