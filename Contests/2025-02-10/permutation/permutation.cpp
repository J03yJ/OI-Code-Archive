#include<bits/stdc++.h>

using namespace std;

ifstream fin("permutation.in");
ofstream fout("permutation.out");
#define cin fin
#define cout fout
#define endl '\n'

int n,lim;
inline void P(vector<int> &v){for(auto it=v.begin();it!=v.end();it++) cout<<*it<<' ';}
inline void R(vector<int> &v){for(auto it=v.rbegin();it!=v.rend();it++) cout<<*it<<' ';}

signed main(){
    cin>>n,lim=__lg(n);

    cout<<4*lim<<endl;
    for(int k=0;k<lim;k++){
        vector<int> p[2];
        for(int i=0;i<n;i++) p[i>>k&1].push_back(i);
        P(p[0]),P(p[1]),cout<<endl;
        R(p[0]),R(p[1]),cout<<endl;
        P(p[1]),P(p[0]),cout<<endl;
        R(p[1]),R(p[0]),cout<<endl;
    }

    return 0;
}