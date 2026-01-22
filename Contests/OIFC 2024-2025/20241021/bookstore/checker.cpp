#include<bits/stdc++.h>

using namespace std;

int main(){
    ifstream fin1("bookstore.in");
    ifstream fin2("bookstore.out");
    int T;
    fin1>>T;
    while(T--){
        int n,m;
        fin1>>n>>m;
        vector<pair<int,int>> a(m+1);
        for(int i=1;i<=m;i++) fin1>>a[i].first>>a[i].second;
        int k1,k2;
        fin2>>k1;
        if(k1==-1) continue ;
        fin2>>k2;
        set<int> s1,s2;
        map<int,int> mp;
        for(int i=1,x;i<=k1;i++){
            fin2>>x;
            mp[x]++;
            s1.insert(a[x].first);
            s1.insert(a[x].second);
        }
        for(int i=1,x;i<=k2;i++){
            fin2>>x;
            mp[x]++;
            s2.insert(a[x].first);
            s2.insert(a[x].second);
        }
        for(auto p:mp){
            if(p.second>1){
                cout<<"More. "<<p.first<<' '<<a[p.first].first<<' '<<a[p.first].second<<endl;
                break ;
            }
        }
        if(s1!=s2) cout<<"Neq."<<endl;
        else cout<<"OK"<<endl;
    }
    return 0;
}