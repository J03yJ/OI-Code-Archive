#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m,q;
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++) cin>>a[i];
        sort(a+1,a+m+1);
        while(q--){
            int x;
            cin>>x;
            int pos=upper_bound(a+1,a+m+1,x)-a-1;
            if(!pos) cout<<a[1]-1<<endl;
            else if(pos==m) cout<<n-a[m]<<endl;
            else cout<<(a[pos+1]-a[pos])/2<<endl;
        }
    }
}