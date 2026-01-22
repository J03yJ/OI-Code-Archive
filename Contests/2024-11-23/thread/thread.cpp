#include<bits/stdc++.h>

using namespace std;

ifstream fin("thread.in");
ofstream fout("thread.out");
#define cin fin
#define cout fout
#define endl '\n'

#define int long long
#define ssiz(x) (signed)x.size()
const int N=1e6+9;

int ans[N],op[N],k[N],tr[N];
vector<int> val;
void Add(int x,int k){
    while(x<=ssiz(val)){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){
    return Ask(r)-Ask(l-1);
}

signed main(){
    int x=1;

    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>op[i]>>k[i];
        if(op[i]==3){
            if(k[i]<0) x=-x;
            else if(!k[i]) x=0;
        }else{
            if(op[i]==2) val.push_back(k[i]);
            else if(op[i]==4) ans[i]=x;
        }
    }
    for(int i=1;i<=m;i++) if(op[i]==1||op[i]==4) val.push_back(k[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    val.insert(val.begin(),(long long)(-1e18+9ll));
    for(int i=1;i<=m;i++) k[i]=lower_bound(val.begin(),val.end(),k[i])-val.begin();
    for(int i=1;i<=m;i++){
        if(op[i]==3) continue ;
        if(op[i]==1||op[i]==2){
            Add(k[i],1);
        }else{
            if(Ask(k[i],k[i])) ans[i]=0;
            else if(Ask(k[i],ssiz(val))&1) ans[i]=-ans[i];
        }
    }
    for(int i=1;i<=ssiz(val);i++) tr[i]=0;
    for(int i=1;i<=m;i++){
        if(op[i]==2) Add(k[i],1);
        else if(op[i]==4){
            if(Ask(k[i],k[i])) ans[i]=1024;
        }
    }
    for(int i=1;i<=m;i++){
        if(op[i]!=4) continue ;
        if(ans[i]==1) cout<<'>'<<endl;
        else if(ans[i]==-1) cout<<'<'<<endl;
        else if(!ans[i]) cout<<'='<<endl;
        else cout<<'!'<<endl;
    }

    return 0;
}