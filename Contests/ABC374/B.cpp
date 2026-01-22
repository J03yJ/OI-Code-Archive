#include<bits/stdc++.h>

using namespace std;

int main(){
    string s,t;
    cin>>s>>t;
    if(s.size()>t.size()) swap(s,t);
    while(s.size()<t.size()) s.push_back('#');

    int pos=0;
    for(int i=0;i<s.size();i++){
        if(s[i]!=t[i]){
            pos=i+1;
            break ;
        }
    }
    cout<<pos<<endl;

    return 0;
}