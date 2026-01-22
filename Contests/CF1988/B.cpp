#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;string s;
        cin>>n>>s;
        int cnt1=0,cnt0=0;
        for(int i=0,lst='1';i<n;i++){
            if(s[i]=='1') cnt1++;
            else if(lst=='1') cnt0++;
            lst=s[i];
        }
        if(cnt0>=cnt1) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}