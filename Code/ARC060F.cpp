#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;

int a[N],b[N],n;
string s,t;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>s;
    n=s.size();
    t=string(s.rbegin(),s.rend());
    s=" "+s,t=" "+t;

    for(int i=2,j=0;i<=n;i++){
        while(j&&s[i]!=s[j+1]) j=a[j];
        if(s[i]==s[j+1]) j++;
        a[i]=j;
    }
    for(int i=2,j=0;i<=n;i++){
        while(j&&t[i]!=t[j+1]) j=b[j];
        if(t[i]==t[j+1]) j++;
        b[i]=j;
    }

    int len=n-a[n];
    if(n%len) len=n;
    if(len==1) cout<<n<<endl<<1<<endl;
    else if(len==n) cout<<1<<endl<<1<<endl;
    else{
        int cnt=0;
        for(int i=1;i<n;i++){
            int lb=i-a[i],rb=(n-i)-b[n-i];
            if(i%lb) lb=i;
            if((n-i)%rb) rb=n-i;
            if(lb==i&&rb==n-i) cnt++;
        }
        cout<<2<<endl<<cnt<<endl;
    }

    return 0;
}