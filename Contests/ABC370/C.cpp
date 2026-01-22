#include<bits/stdc++.h>

using namespace std;

int main(){
    string s,t;
    cin>>s>>t;
    vector<string> v;
    for(int i=0;i<s.size();i++){
        if(s[i]>t[i]){
            s[i]=t[i];
            v.push_back(s);
        }
    }
    for(int i=s.size()-1;~i;i--){
        if(s[i]<t[i]){
            s[i]=t[i];
            v.push_back(s);
        }
    }
    
    cout<<v.size()<<endl;
    for(string x:v) cout<<x<<endl;

    return 0;
}