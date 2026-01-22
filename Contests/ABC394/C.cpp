#include<bits/stdc++.h>

using namespace std;

signed main(){
    string s;
    cin>>s;

    for(int i=0;i<s.size();){
        if(s[i]=='W'&&s[i+1]=='A'){
            s[i]='A',s[i+1]='C';
            i=max(0,i-1);
        }else i++;
    }

    cout<<s<<endl;

    return 0;
}