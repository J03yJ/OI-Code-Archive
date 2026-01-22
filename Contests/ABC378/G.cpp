#include<bits/stdc++.h>

using namespace std;

const int N=2e2+9;

int p[N];

int main(){
    int a,b,m;
    cin>>a>>b>>m;
    for(int i=1;i<a*b;i++) p[i]=i;
    do{
        vector<int> f;
        for(int i=1;i<a*b;i++){
            if(!f.size()||p[i]>f.back()) f.push_back(p[i]);
            else{
                auto it=upper_bound(f.begin(),f.end(),p[i]);
                *it=p[i];
            }
        }
        vector<int> g;
        for(int i=1;i<a*b;i++){
            if(!g.size()||-p[i]>g.back()) g.push_back(-p[i]);
            else{
                auto it=upper_bound(g.begin(),g.end(),-p[i]);
                *it=-p[i];
            }
        }
        for(int &x:g) x=-x;
        // for(int i=1;i<a*b;i++) cout<<p[i]<<' ';cout<<" : "<<endl;
        // for(int x:f) cout<<x<<' ';cout<<endl;
        // for(int x:g) cout<<x<<' ';cout<<endl;
        // cout<<endl;
        if(f.size()==a&&g.size()==b&&f.back()>g.back()){
            for(int i=1;i<a*b;i++) cout<<p[i]<<' ';cout<<" : "<<endl;
            for(int x:f) cout<<x<<' ';cout<<endl;
            for(int x:g) cout<<x<<' ';cout<<endl;
            cout<<endl;
        }
    }while(next_permutation(p+1,p+a*b));

    return 0;
}