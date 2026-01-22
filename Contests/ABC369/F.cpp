#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int f[N],pre[N],n,h,w;

pair<int,int> tr[N],a[N];
void Add(int x,pair<int,int> k){
    while(x<=w){
        tr[x]=max(tr[x],k);
        x+=x&-x;
    }
}
pair<int,int> Ask(int x){
    pair<int,int> ans={0,0};
    while(x){
        ans=max(ans,tr[x]);
        x&=x-1;
    }
    return ans;
}

int main(){
    cin>>h>>w>>n;
    for(int i=1;i<=n;i++) cin>>a[i].first>>a[i].second;
    a[0]={1,1};
    a[++n]={h,w};

    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        pair<int,int> tmp=Ask(a[i].second);
        f[i]=tmp.first+1;
        pre[i]=tmp.second;
        Add(a[i].second,{f[i],i});
    }

    string s="";
    int cur=n;
    while(cur){
        int x=a[cur].first-a[pre[cur]].first;
        int y=a[cur].second-a[pre[cur]].second;
        for(int i=1;i<=x;i++) s.push_back('D');
        for(int i=1;i<=y;i++) s.push_back('R');
        cur=pre[cur];
    }
    reverse(s.begin(),s.end());
    cout<<f[n]-1<<endl<<s<<endl;

    return 0;
}