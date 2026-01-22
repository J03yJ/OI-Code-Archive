#include<bits/stdc++.h>

using namespace std;

ifstream fin("matching.in");
ifstream ffin("matching.out");
ofstream fout("checker.out");
#define cin fin
#define cout fout
#define endl '\n'

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
const int N=2e5+9;

int a[N],n;

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        string s;
        ffin>>s;
        if(s=="No") continue ;
        map<int,int> mp;
        for(int p=1,i,j;p<=n/2;p++){
            ffin>>i>>j;
            if(mp[i]||mp[j]) cout<<"Case "<<T<<" Exceed."<<endl;
            if(abs(a[i]-a[j])!=abs(i-j)) cout<<"Case "<<T<<" Neq."<<endl;
        }
    }
    cout<<"Done. "<<endl;

    return 0;
}