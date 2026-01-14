#include<bits/stdc++.h>

using namespace std;

int main(){
    array<int,4> a;
    for(int i=0;i<4;i++) cin>>a[i];

    priority_queue<int> q;
    int cnt=0;
    for(int i=0;i<4;i++) q.push(a[i]);
    while(q.size()){
        int x=q.top();
        q.pop();
        if(!q.size()) break ;
        if(x==q.top()) q.pop(),cnt++;
    }

    cout<<cnt<<endl;

    return 0;
}