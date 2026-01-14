#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

void Solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int &x:a) cin>>x;
    sort(a.begin(),a.end());
    int mn=1e9,p=0,q=0;
    for(int i=0;i+1<ssiz(a);i++){
        if(a[i]==a[i+1]){
            if(p){
                cout<<a[i]<<' '<<a[i+1]<<' '<<a[p-1]<<' '<<a[p]<<endl;
                return ;
            }else p=i+1,i++;
        }
    }
    if(!p){
        cout<<-1<<endl;
        return ;
    }
    int x=a[p];
    a.erase(a.begin()+p-1,a.begin()+p+1);
    for(int i=0;i+1<ssiz(a);i++){
        if(a[i+1]-a[i]<2*x){
            cout<<a[i]<<' '<<a[i+1]<<' '<<x<<' '<<x<<endl;
            return ;
        }
    }
    cout<<-1<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}