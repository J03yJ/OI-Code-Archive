#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int &x:a) cin>>x;
        bool flag=0;
        for(int i=1;i<n;i++){
            int x=a[i-1],y=a[i];
            if(y<2*x&&x<2*y){
                flag=1;
                cout<<"Yes"<<endl;
                break ;
            }
        }
        if(!flag) cout<<"No"<<endl;
    }
}