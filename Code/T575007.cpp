#include<bits/stdc++.h>

using namespace std;

int ask(int ,int );
int solve(int n){
    vector<int> s(n),trs;
    iota(s.begin(),s.end(),0);

    int p=1,T=0;
    while(T++){
        int mx=0,x=s.back();
        s.pop_back();
        vector<int> res,cnt(n/p+1,0);
        for(int i=0;i<s.size();i++){
            res.push_back(ask(s[i],x));
            mx=max(mx,res.back());
            cnt[res.back()/p]++;
        }
        bool flag=0;
        for(int i=1;i*p<n;i++) ;

        vector<int> t;

        for(int i=0;i<s.size();i++){
            if(res[i]==mx) t.push_back(s[i]);
            else if(T==1) trs.push_back(s[i]);
        }
        s=t,p=x;
    }
}