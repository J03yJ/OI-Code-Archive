#include<bits/stdc++.h>

using namespace std;

ifstream fin("rotate.in");
ofstream fout("rotate.out");
#define cin fin
#define cout fout

string s,t;
int Hash(string s){
    int x=0;
    for(char c:s){
        x*=131;
        x+=c;
    }
    return x;
}

map<int,int> mp;
string Rotate(string s,int l,int r){
    for(int i=r;i>l;i--) swap(s[i],s[i-1]);
    return s;
}
int DFS(string s){
    int x=Hash(s);
    if(mp[x]) return mp[x];
    int ans=s.size()+1;
    for(int i=0;i<s.size();i++){
        if(s[i]==t[i]) continue ;
        for(int j=i;j<s.size();j++){
            if(s[j]==t[i]) ans=min(ans,DFS(Rotate(s,i,j))+1);
        }
        break ;
    }
    return ans;
}

int Check(){
    map<int,int> mps,mpt;
    for(char c:s) mps[c]++;
    for(char c:t) mpt[c]++;
    for(int i=0;i<128;i++) if(mps[i]!=mpt[i]) return 1;
    return 0;
}

signed main(){
    cin>>s>>t;
    if(Check()){
        cout<<-1<<endl;
        return 0;
    }

    mp[Hash(t)]=1;
    cout<<DFS(s)-1<<endl;

    return 0;
}