#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin>>s;
    while(s.back()=='0') s.pop_back();
    if(s.back()=='.') s.pop_back();
    cout<<s<<endl;
    return 0;
}