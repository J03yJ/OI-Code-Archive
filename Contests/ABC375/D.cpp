#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin>>s;
    vector<int> buc(26,0);
    vector<vector<int>> pre(s.size(),vector<int>(26,0));
    vector<vector<int>> suc(s.size(),vector<int>(26,0));
    for(int i=0;i<s.size();i++){
        for(int j=0;j<26;j++) pre[i][j]=buc[j];
        buc[s[i]-'A']++;
    }
    buc=vector<int>(26,0);
    for(int i=s.size()-1;~i;i--){
        for(int j=0;j<26;j++) suc[i][j]=buc[j];
        buc[s[i]-'A']++;
    }

    long long ans=0;
    for(int i=0;i<s.size();i++){
        for(int j=0;j<26;j++) ans+=1ll*suc[i][j]*pre[i][j];
    }
    cout<<ans<<endl;

    return 0;
}