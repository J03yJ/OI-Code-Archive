#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
char c[N];
int a[N],acnt,b[N],bcnt;

int main(){
    int n,T;
    cin>>n>>T;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(c[i]=='0') a[++acnt]=x;
        else b[++bcnt]=x;
    }
    sort(a+1,a+acnt+1);
    sort(b+1,b+bcnt+1);
    long long ans=0;
    deque<int> q;
    for(int i=1,j=1;i<=acnt;i++){
        while(j<=bcnt&&a[i]>b[j]) q.push_back(b[j++]);
        while(q.size()&&q.front()+2*T<a[i]) q.pop_front();
        ans+=q.size();
    }
    cout<<ans<<endl;
}