#include<bits/stdc++.h>

using namespace std;

int Check(string s){
    int cnt=0;
    map<string,int> mp;
    for(int i=0;i<s.size();i++){
        string t="";
        for(int j=i;j<s.size();j++){
            t+=s[j];
            cnt+=!mp[t];
            mp[t]=1;
        }
    }
    return cnt;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        if(s.size()==1) cout<<-1<<endl;
        else if(s.size()==2){
            if(s[0]==s[1]) cout<<s<<endl;
            else cout<<-1<<endl;
        }else{
            int f=0;
            for(int i=1;i<s.size();i++){
                if(s[i]==s[i-1]){
                    cout<<s[i-1]<<s[i]<<endl;
                    f=1;
                    break ;
                }
            }
            if(f) continue ;
            for(int i=2;i<s.size();i++){
                if(s[i]==s[i-2]) continue ;
                cout<<s[i-2]<<s[i-1]<<s[i]<<endl;
                f=1;
                break ;
            }
            if(!f) cout<<-1<<endl;
        }
    }

    return 0;
}