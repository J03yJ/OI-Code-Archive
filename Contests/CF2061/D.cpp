#include<bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<int> a(n),b(m);
        for(int &x:a) cin>>x;
        for(int &x:b) cin>>x;

        long long suma=0,sumb=0;
        for(int x:a) suma+=x;
        for(int x:b) sumb+=x;
        if(suma!=sumb){
            cout<<"No"<<endl;
            continue ;
        }

        multiset<int> s,t;
        for(int x:a) s.insert(x);
        for(int x:b){
            auto it=s.lower_bound(x);
            if(it!=s.end()&&*it==x) s.erase(it);
            else t.insert(x);
        }
        while(t.size()&&s.size()){
            int x=*t.rbegin();
            t.erase(t.lower_bound(x));
            if(x<*s.rbegin()) break ;

            int y=x>>1,z=(x+1)>>1;
            
            auto it=s.lower_bound(y);
            if(it!=s.end()&&*it==y) s.erase(it);
            else t.insert(y);

            auto jt=s.lower_bound(z);
            if(jt!=s.end()&&*jt==z) s.erase(jt);
            else t.insert(z);

            // cout<<x<<' '<<y<<' '<<z<<" : "<<endl;
            // for(int x:s) cout<<x<<' ';cout<<endl;
            // for(int x:t) cout<<x<<' ';cout<<endl;
        }

        if(s.size()||t.size()) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }

    return 0;
}