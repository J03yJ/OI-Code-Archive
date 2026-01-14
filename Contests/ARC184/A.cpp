#include<bits/stdc++.h>

using namespace std;

const int N=1e3+9;
int f[N][N],fl[N];

int main(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> c;
    for(int i=1;i<=n;){
        c.push_back(vector<int>());
        for(int j=1;i<=n&&j<=11;i++,j++) c.back().push_back(i);
        // for(int x:c.back()) cout<<x<<' ';cout<<endl;
    }
    for(int i=0;i<c.size();i++){
        for(int j=1,op;j<c[i].size();j++){
            cout<<"? "<<c[i][j-1]<<' '<<c[i][j]<<endl;
            cin>>op;
            if(op) fl[i]=1;
            f[i][j]=f[i][j-1]^op;
        }
        if(c[i].size()!=11) fl[i]=1;
    }
    vector<int> tr,fk;
    for(int i=0;i<c.size();i++){
        if(fl[i]) continue ;
        for(int x:c[i]) tr.push_back(x);
    }
    for(int i=0,op;i<c.size();i++){
        if(!fl[i]) continue ;
        cout<<"? "<<tr.front()<<' '<<c[i].front()<<endl;
        cin>>op;
        for(int j=0;j<c[i].size();j++){
            if(f[i][j]^op) fk.push_back(c[i][j]);
            else tr.push_back(c[i][j]);
        }
    }
    cout<<"! ";
    for(int x:fk) cout<<x<<' ';
    cout<<endl;
}