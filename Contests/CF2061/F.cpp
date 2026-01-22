#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
void Solve(){
    string s,t;
    cin>>s>>t;
    vector<pair<int,int>> a,b;
    for(int i=0,j=0;i<ssiz(s);i=j){
        while(j<ssiz(s)&&s[i]==s[j]) j++;
        a.push_back({j-i,s[i]-'0'});
    }
    for(int i=0,j=0;i<ssiz(t);i=j){
        while(j<ssiz(t)&&t[i]==t[j]) j++;
        b.push_back({j-i,t[i]-'0'});
    }
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());

    int cnt=0;
    while(ssiz(b)){
        int len[2]={0,0};
        int op=b.back().second,trg=b.back().first;
        b.pop_back();
        // cout<<op<<' '<<trg<<endl;
        if(ssiz(a)) if(a.back().second==op) cnt--;
        while(ssiz(a)&&len[op]<trg){
            len[a.back().second]+=a.back().first;
            // cout<<" : "<<a.back().first<<' '<<a.back().second<<endl;
            if(a.back().second==op) cnt++;
            a.pop_back();
        }
        // cout<<"! "<<len[0]<<' '<<len[1]<<endl;
        if(len[op]!=trg){
            cout<<-1<<endl;
            return ;
        }
        if(!len[!op]) continue ;
        if(ssiz(a)&&a.back().second!=op) a.back().first+=len[!op];
        else a.push_back({len[!op],!op});
    }
    if(ssiz(b)||ssiz(a)) cout<<-1<<endl;
    else cout<<cnt<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}