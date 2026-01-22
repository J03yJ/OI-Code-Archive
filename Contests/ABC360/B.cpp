#include<bits/stdc++.h>

using namespace std;

int main(){
    string s,t;
    cin>>s>>t;
    for(int i=1;i<s.size();i++){
        for(int c=1;c<=i;c++){
            string tmp="";
            for(int j=c-1;j<s.size();j+=i) tmp+=s[j];
            if(tmp==t){
                cout<<"Yes"<<endl;
                return 0;
            }
        }
    }
    cout<<"No"<<endl;
}