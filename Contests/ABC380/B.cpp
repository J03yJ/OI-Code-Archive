#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin>>s;
    int lst=0;
    for(int i=1;i<s.size();i++){
        if(s[i]=='|') cout<<i-lst-1<<' ',lst=i;
    }
    cout<<endl;
}