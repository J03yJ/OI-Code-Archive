#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int r,c,n;
bool Check(int x,int y){
    return !x||!y||x==r||y==c;
}
int Trs(int x,int y){
    if(!x) return y; // U
    else if(y==c) return x+c; // R
    else if(x==r) return c+r+c-y; // D
    else return c+c+r+r-x; // L
}

int main(){
    cin>>r>>c>>n;
    vector<pair<int,int>> p;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        if(!Check(x1,y1)||!Check(x2,y2)) continue ;
        p.push_back({Trs(x1,y1),i});
        p.push_back({Trs(x2,y2),i});
    }

    sort(p.begin(),p.end());
    vector<int> stk;
    for(pair<int,int> x:p){
        if(stk.size()&&stk.back()==x.second) stk.pop_back();
        else stk.push_back(x.second);
    }

    if(stk.size()) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;

    return 0;
}