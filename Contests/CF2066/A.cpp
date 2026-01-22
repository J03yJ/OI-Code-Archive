#include<bits/stdc++.h>

using namespace std;

inline void Solve(){
    int n;
    cin>>n;
    vector<int> a(n+1,0),r(n+1,0);
    for(int i=1;i<=n;i++) cin>>a[i],r[a[i]]=i;

    int x,y;
    for(int i=1;i<=n;i++){
        if(!r[i]){
            cout<<"? "<<i<<' '<<a[1]<<endl;
            cin>>x;
            if(x) cout<<"! B"<<endl;
            else cout<<"! A"<<endl;
            return ;
        }
    }
    cout<<"? "<<r[1]<<' '<<r[n]<<endl;
    cin>>x;
    cout<<"? "<<r[n]<<' '<<r[1]<<endl;
    cin>>y;
    if(x==y&&x>=n-1) cout<<"! B"<<endl;
    else cout<<"! A"<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}