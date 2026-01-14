#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int a[N],n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];

        int cnt=0;
        a[n+1]=0;
        for(int i=1;i+2<=n;i++){
            if(a[i]==a[i+2]&&a[i]!=a[i+1]){
                if(a[i+2]!=a[i+3]) swap(a[i+1],a[i+2]);
                else swap(a[i],a[i+1]);
                cnt++;
            }
        }
        for(int i=1;i<=n;i++) if(a[i]!=a[i-1]) cnt++;
        
        cout<<cnt<<endl;
    }

    return 0;
}