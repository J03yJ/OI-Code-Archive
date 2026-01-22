#include<bits/stdc++.h>

using namespace std;

ifstream fin("string.in");
ofstream fout("string.ans");
#define cin fin
#define cout fout

const int N=2e3+9;

string s[N];
int n,m,k;

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>s[i];

    for(int i=1;i<=n;i++){
        int err=0;
        for(int j=1;j<=n;j++){
            if(i==j) continue ;
            int cnt=0;
            for(int k=0;k<m;k++) if(s[i][k]!=s[j][k]) cnt++;
            if(cnt!=k){
                err=-1;
                break ;
            }
        }
        if(!err) cout<<i<<' ';
    }
    cout<<endl;

    return 0;
}