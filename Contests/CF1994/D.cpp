#include<bits/stdc++.h>

using namespace std;

const int N=3e3+9;

int a[N];
vector<pair<int,int>> buc[N];

int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    fa[find(y)]=find(x);
}

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) fa[i]=i;

        vector<pair<int,int>> ans;
        for(int i=n-1;i>=1;i--){
            for(int j=1;j<=n;j++) buc[a[j]%i].push_back({find(j),j});
            for(int j=0;j<i;j++){
                for(pair<int,int> x:buc[j]){
                    for(pair<int,int> y:buc[j]){
                        if(x.first==y.first) continue ;
                        merge(x.first,y.first);
                        ans.emplace_back(x.second,y.second);
                        break ;
                    }
                    if(ans.size()==n-i) break ;
                }
                if(ans.size()==n-i) break ;
            }
            for(int j=0;j<i;j++) buc[j].clear();
        }

        reverse(ans.begin(),ans.end());
        if(ans.size()!=n-1) cout<<"NO"<<endl;
        else{
            cout<<"YES"<<endl;
            for(pair<int,int> p:ans) cout<<p.first<<' '<<p.second<<endl;
        }

    }
}