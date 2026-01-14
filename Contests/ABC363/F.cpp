#include<bits/stdc++.h>

using namespace std;

#define int long long

bool palin(string s){
    for(int i=0;i<s.size();i++) if(s[i]!=s[s.size()-i-1]) return 0;
    return 1;
}
string srev(string s){
    string t="";
    for(int i=s.size()-1;~i;i--) t+=s[i];
    return t;
}
string strs(int x){
    string s="";
    while(x){
        s+=char('0'+x%10);
        x/=10;
    }
    return srev(s);
}
int itrs(string s){
    int x=0;
    for(int i=0;i<s.size();i++){
        x*=10;
        x+=s[i]-'0';
    }
    return x;
}
int irev(int x){
    return itrs(srev(strs(x)));
}
bool z(int x){
    while(x){
        if(x%10==0) return 1;
        x/=10;
    }
    return 0;
}

string ans="";
map<int,int> vis;
void dfs(int x){
    if(vis[x]) return ;
    vis[x]=1;
    if(palin(strs(x))&&!z(x)){
        ans=strs(x);
        return ;
    }
    for(int i=2;i*i<=x;i++){
        if(x%i) continue ;
        if(!z(i)&&x%(irev(i)*i)==0){
            dfs(x/i/irev(i));
            if(ans!=""){
                ans=strs(i)+"*"+ans+"*"+srev(strs(i));
                return ;
            }
        }
        if(i*i!=x){
            if(!z((x/i))&&x%(irev((x/i))*(x/i))==0){
                dfs(x/(x/i)/irev((x/i)));
                if(ans!=""){
                    ans=strs((x/i))+"*"+ans+"*"+srev(strs((x/i)));
                    return ;
                }
            }
        }
    }
}

signed main(){
    int x;
    cin>>x;
    dfs(x);
    if(ans!="") cout<<ans<<endl;
    else cout<<-1<<endl;
}