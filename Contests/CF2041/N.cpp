#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;

int a[N],p[N],mn[N],mn2[N],n,m;
vector<int> ng[N],son[N];
int Find(vector<int> &v,int x){
    auto it=lower_bound(v.begin(),v.end(),x);
    if(it==v.end()) return 0;
    else return *it==x;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],p[i]=i;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        ng[u].push_back(v);
        ng[v].push_back(u);
    }
    for(int i=1;i<=n;i++) ng[i].push_back(i),sort(ng[i].begin(),ng[i].end());

    int sum=0,cnt=0;
    sort(p+1,p+n+1,[](int x,int y){return a[x]<a[y];});
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(Find(ng[i],p[j])) continue ;
            if(!mn[i]) mn[i]=p[j];
            else{
                mn2[i]=p[j];
                break ;
            }
        }
        // cout<<mn[i]<<' '<<a[mn[i]]<<' '<<mn2[i]<<' '<<a[mn2[i]]<<endl;
        sum+=a[i];
        if(mn[i]) son[mn[i]].push_back(i),sum+=a[mn[i]];
        else cnt++;
    }

    if(cnt==2){
        for(int i=1;i<=n;i++) cout<<-1<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(cnt&&mn[i]){
            cout<<-1<<' ';
            continue ;
        }

        int err=0,ans=sum,pos=p[1];
        if(pos==i) pos=p[2];
        ans-=a[i],ans-=a[mn[i]];
        ans-=a[pos],ans-=a[mn[pos]];

        cout<<ans<<' '<<sum<<' '<<pos<<endl;

        for(int x:son[i]){
            if(x==pos) continue ;
            cout<<i<<" : "<<x<<' '<<a[mn2[x]]-a[mn[x]]<<endl;
            if(mn2[x]) ans-=a[mn[x]],ans+=a[mn2[x]];
            else err=1;
        }
        
        // if(err) cout<<-1<<' ';
        // else cout<<ans<<' ';
    }
    cout<<endl;

    return 0;
}