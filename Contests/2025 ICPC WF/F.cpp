#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int p[N],d[N],ddl[N],ok[N],st[N],gt[N],cnt[N],ans[N],n,m;
vector<int> t[N],bel[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>p[i]>>d[i];
            cnt[p[i]]++;
            t[i]=vector<int>(d[i]);
            for(auto &x:t[i]) cin>>x,bel[x].push_back(i);
            sort(t[i].begin(),t[i].end());
        }

        for(int i=1;i<=m;i++) ddl[i]=1;
        for(int i=1;i<=n;i++) for(int j:t[i]) ddl[j]=max(ddl[j],p[i]);
        for(int i=1;i<=m;i++){
            int c=0,s=0;
            for(int j:bel[i]) c=max(c,p[j]);
            for(int j:bel[i]) if(p[j]==c) s++;
            if(!c) continue ;
            if(st[c]) continue ;
            if(s<cnt[c]) continue ;
			ans[c]=i;
            st[c]=gt[i]=1;
            for(int j:bel[i]) if(p[j]==c) ok[j]=1;
        }

        bool flag=1;
        priority_queue<array<int,2>> q;
		for(int i=1;i<=n;i++) if(!ok[i]) flag=0;
        for(int i=1;i<=m;i++) if(!gt[i]) q.push({ddl[i],i});
        for(int i=m;i>=1;i--){
            if(st[i]) continue ;
            if(q.top()[0]>i){
                flag=0;
                break ;
            }else ans[i]=q.top()[1],q.pop();
        }

        if(flag){
			cout<<"yes"<<endl;
			// for(int i=1;i<=m;i++) cout<<ans[i]<<' ';cout<<endl;
		}else cout<<"no"<<endl;

        for(int i=1;i<=n;i++){
            p[i]=d[i]=ok[i]=0;
            t[i].clear();
        }
        for(int i=1;i<=m;i++){
            ddl[i]=st[i]=gt[i]=cnt[i]=0;
            bel[i].clear();
        }
    }

    return 0;
}