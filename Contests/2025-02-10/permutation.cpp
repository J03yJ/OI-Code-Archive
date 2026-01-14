#include<bits/stdc++.h>

using namespace std;

ifstream fin("permutation.in");
ofstream fout("permutation.out");
#define cin fin
#define cout fout
#define endl '\n'

const int B=9;
const int N=2048;

int n;
vector<string> id;
inline void DFS(int dep,string s,int sum){
    if(sum>B) return ;
    if(!dep){
        if(sum==B) id.push_back(s);
        return ;
    }
    for(int i:{0,1,2}){
        if(dep==1&&i==2) continue ;
        string t=s;
        t.push_back(i+'0');
        DFS(dep-1,t,sum+i);
        if(id.size()>=N) return ;
    }
}
inline void P(vector<int> &v){for(auto it=v.begin();it!=v.end();it++) if(*it<n) cout<<*it<<' ';}
inline void R(vector<int> &v){for(auto it=v.rbegin();it!=v.rend();it++) if(*it<n) cout<<*it<<' ';}

signed main(){
    cin>>n;
    DFS(B,"",0);
    cout<<26<<endl;
    for(int i=0;i<B;i++){
        if(i+1<B){
            vector<int> v[3];
            for(int j=0;j<N;j++) v[id[j][i]-'0'].push_back(j);
            P(v[0]),P(v[1]),P(v[2]),cout<<endl;
            R(v[0]),P(v[2]),R(v[1]),cout<<endl;
            R(v[1]),P(v[0]),R(v[2]),cout<<endl;
        }else{
            vector<int> v[2];
            for(int j=0;j<N;j++) v[id[j][i]-'0'].push_back(j);
            P(v[0]),P(v[1]),cout<<endl;
            R(v[0]),R(v[1]),cout<<endl;
        }
    }
}