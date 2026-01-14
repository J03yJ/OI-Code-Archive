#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n,0);
        for(int &x:a) cin>>x;

        vector<pair<int,int>> ans;
        vector<int> pos[3];
        for(int i=0;i<n;i++) pos[a[i]].push_back(i);
        int l=ssiz(pos[0]),r=ssiz(pos[0])+ssiz(pos[1]);
        for(int i=1,j=l;i<ssiz(pos[1]);i++){
            int x=pos[1][i];
            if(l<=x&&x<r) continue ;
            while(j<r&&a[j]==1) j++;
            swap(a[x],a[j]);
            ans.push_back({x,j});
        }

        int p=pos[1][0];
        if(l<=p&&p<r){
            for(int i=0;i<n;i++){
                if(i<l&&a[i]==2){
                    swap(a[i],a[p]);
                    ans.push_back({p,i});
                    p=i;
                    break ;
                }
            }
        }

        for(int k:{0,1,2}) pos[k].clear();
        for(int i=0;i<n;i++){
            if(i<r&&a[i]==2) pos[2].push_back(i);
            if(i>=l&&a[i]==0) pos[0].push_back(i);
        }
        reverse(pos[2].begin(),pos[2].end());
        while(p<l||p>=r){
            int x;
            if(p<l){
                x=pos[0].back();
                pos[0].pop_back();
            }else{
                x=pos[2].back();
                pos[2].pop_back();
            }
            swap(a[x],a[p]);
            ans.push_back({p,x});
            p=x;
        }

        cout<<ssiz(ans)<<endl;
        for(auto t:ans) cout<<t.first+1<<' '<<t.second+1<<endl;
        // for(int x:a) cout<<x<<' ';cout<<endl;
    }

    return 0;
}