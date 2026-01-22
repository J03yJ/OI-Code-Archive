#include<bits/stdc++.h>

using namespace std;

ifstream fin("str.in");
ofstream fout("str.out");
#define cin fin
#define cout fout
#define endl '\n'

const int T=1.5e3+9;
const int Q=1.3e6+9;
const int S=1e5+9;
const int L=1.5e3;

int len[Q],cnt=25,n,m,q;
unsigned w[Q];
bitset<T> pre[Q],suf[Q],ocr[Q],lsh[T],rsh[T];
inline int Merge(int x,int y){
    int z=++cnt;
    w[z]=w[x]+w[y];
    w[z]+=(suf[x]&pre[y]).count();
    len[z]=min(len[x]+len[y],L+1);
    pre[z]=pre[x],suf[z]=suf[y];
    if(len[x]<L) pre[z]|=((pre[y]&rsh[len[x]])>>len[x])&ocr[x];
    if(len[y]<L) suf[z]|=((suf[x]&lsh[len[y]])&ocr[y])<<len[y];
    if(len[z]<L) ocr[z]=ocr[x]&((ocr[y]&rsh[len[x]])>>len[x]);
    return z;
}

int id[Q];
string s[S],t[T];

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=m;i++) cin>>s[i];

    int lsum=0;
    for(int i=0;i<26;i++) len[i]=1;
    for(int i=1;i<=n;i++){
        int l=t[i].size();
        for(int j=0;j<l;j++){
            int p=lsum+j+1;
            ocr[t[i][j]-'a'].set(p);
            for(int k=1;k<=j;k++) rsh[k].set(p);
            for(int k=1;k<=l;k++) if(j+k<l) lsh[k].set(p);
        }
        if(l==1) w[t[i][0]-'a']++;
        else{
            suf[t[i][0]-'a'].set(lsum+2);
            pre[t[i][l-1]-'a'].set(lsum+l);
        }
        lsum+=l;
    }

    for(int i=1;i<=m;i++){
        id[i]=-1;
        for(char c:s[i]){
            if(!~id[i]) id[i]=c-'a';
            else id[i]=Merge(id[i],c-'a');
        }
        cout<<w[id[i]]<<endl;
    }
    for(int i=1,x,y;i<=q;i++){
        cin>>x>>y;
        id[m+i]=Merge(id[x],id[y]);
        cout<<w[id[m+i]]<<endl;
    }

    return 0;
}