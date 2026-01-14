#include<bits/stdc++.h>

using namespace std;

ifstream fin("easygame.in");
ofstream fout("easygame.out");
#define cin fin
#define cout fout

#define ssiz(x) (signed)x.size()

const int N=1e5+9;

int a[N],pre[N][26],c[N],buc[N],n,cnt;

int main(){
    string s;
    cin>>s;
    n=ssiz(s);

    unordered_map<int,int> mp;
    mp[0]=++cnt;
    for(int i=1;i<=n;i++) a[i]=s[i-1]-'a';
    for(int i=1;i<=n;i++){
        for(int k=0;k<26;k++) pre[i][k]=pre[i-1][k];
        pre[i][a[i]]++;
        for(int k=0;k<26;k++) c[i]|=(pre[i][k]&1)<<k;
        if(!mp[c[i]]) mp[c[i]]=++cnt;
        // cout<<c[i]<<endl;
    }

    int ans=0;
    for(int i=0;i<=cnt;i++) buc[i]=-1;
    buc[mp[0]]=0;
    for(int i=1;i<=n;i++){
        if(~buc[mp[c[i]]]) ans=max(ans,i-buc[mp[c[i]]]);
        for(int k=0;k<26;k++){
            if(~buc[mp[c[i]^(1<<k)]]) ans=max(ans,i-buc[mp[c[i]^(1<<k)]]);
        }
        if(!~buc[mp[c[i]]]) buc[mp[c[i]]]=i;
    }
    cout<<ans<<endl;

    return 0;
}