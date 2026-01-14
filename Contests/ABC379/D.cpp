#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main(){
    int T,dlt=0;
    cin>>T;
    priority_queue<int> q;
    while(T--){
        int op;
        cin>>op;
        if(op==1) q.push(-dlt);
        else if(op==2){
            int x;
            cin>>x;
            dlt+=x;
        }else if(op==3){
            int x;
            cin>>x;
            x-=dlt;
            int cnt=0;
            while(q.size()&&q.top()>=x) cnt++,q.pop();
            cout<<cnt<<endl;
        }
    }
}