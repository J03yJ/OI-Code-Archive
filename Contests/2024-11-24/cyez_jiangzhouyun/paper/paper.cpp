#include<bits/stdc++.h>

using namespace std;

ifstream fin("paper.in");
ofstream fout("paper.out");
#define cin fin
#define cout fout

#define int long long
const int N=1e6+9;

int a[N],b[N],n;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    vector<int> cur;
    for(int i=1;i<=n;i++){
        vector<int> tmp;
        for(int j=0;j<cur.size();j+=2){
            tmp.push_back(cur[j]+cur[j+1]);
        }
        cur=tmp;
        for(int j=0;j<(1<<(n-i));j++) cur.push_back(a[i]+b[i]*j);
        sort(cur.begin(),cur.end());
        cur.erase(cur.begin()+(1<<(n-i)),cur.end());
    }
    cout<<cur.back()<<endl;

    return 0;
}