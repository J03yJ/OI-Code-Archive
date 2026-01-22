#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;

int a[N],b[N],n;

long long Calc(int *a){
    priority_queue<int> q;
    long long ans=0;
    for(int i=1;i<=n;i++){
        q.push(a[i]);
        if(a[i]<q.top()){
            ans+=q.top()-a[i];
            q.pop();
            q.push(a[i]);
        }
    }
    return ans;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=1e9-a[i];
    
    cout<<min(Calc(a),Calc(b))<<endl;

    return 0;
}