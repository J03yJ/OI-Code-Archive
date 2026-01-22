#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;
int a[N];
bool c[N];

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> L;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        L.emplace_back(x);
        c[x]=1;
    }
    sort(L.begin(),L.end());
    
    if(L.front()==1||L.back()==n){
        cout<<-1<<endl;
        return 0;
    }

    int lst=1;
    for(int i=1;i<=n;i++){
        if(!c[i]) a[i]=lst,lst=i+1;
        else a[i]=i+1;
    }

    for(int i=1;i<=n;i++){
        cout<<a[i]<<' ';
    }
    cout<<endl;
}