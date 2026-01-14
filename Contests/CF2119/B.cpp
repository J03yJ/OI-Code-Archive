#include<bits/stdc++.h>

using namespace std;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n,px,py,qx,qy;
        cin>>n>>px>>py>>qx>>qy;
        vector<double> a(n);
        for(double &x:a) cin>>x;
        a.push_back(hypotl(px-qx,py-qy));
        sort(a.begin(),a.end());
        double sum=1e-15;
        for(double &x:a) sum+=x;    
        if(2*a.back()>sum) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }

    return 0;
}