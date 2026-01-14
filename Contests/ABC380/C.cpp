#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    int n,k;
    cin>>n>>k>>s;
    s.insert(s.begin(),'0');
    string t=s;
    for(int i=1,cnt=0,p=0;i<=n;i++){
        if(s[i]=='1'&&s[i-1]=='0') cnt++;
        if(s[i]=='0'&&s[i-1]=='1'&&cnt==k-1) p=i;
        if(cnt==k&&s[i]=='1') swap(t[p++],t[i]);
        // cout<<cnt<<' '<<p<<endl;
    }
    t.erase(t.begin());
    cout<<t<<endl;
}