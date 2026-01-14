#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e6+9;

int a[N];
int QueryMin(int l,int r,set<int> &s){
    if(l>r) return 0;
    auto it=s.lower_bound(l);
    if(it==s.end()) return 0;
    if((*it)<=r) return *it;
    else return 0;
}
int QueryMax(int l,int r,set<int> &s){
    if(l>r) return 0;
    auto it=--s.upper_bound(r);
    if((*it)>=l) return *it;
    else return 0;
}

signed main(){
    int T;
    cin>>T;
    map<string,int> mp;
    mp["BG"]=1;
    mp["BR"]=2;
    mp["BY"]=3;
    mp["GR"]=4;
    mp["GY"]=5;
    mp["RY"]=6;
    while(T--){
        int n,q;
        cin>>n>>q;
        set<int> s[7];
        for(int i=1;i<=n;i++){
            string typ;
            cin>>typ;
            s[a[i]=mp[typ]].insert(i);
        }
        for(int i=1;i<=6;i++) s[i].insert(0);

        while(q--){
            int l,r;
            cin>>l>>r;
            if(l>r) swap(l,r);
            if((a[l]^a[r])!=7) cout<<abs(r-l)<<endl;
            else{
                int pos=0;
                for(int i=1;i<=6;i++){
                    if(i==a[l]||i==a[r]) continue ;
                    pos=QueryMax(l,r,s[i]);
                    if(pos) break ;
                }
                if(pos){
                    cout<<abs(r-l)<<endl;
                    continue ;
                }
                int posl=0,posr=n+1;
                for(int i=1;i<=6;i++){
                    if(i==a[l]||i==a[r]) continue ;
                    int tmpl=QueryMax(1,l-1,s[i]);
                    if(tmpl) posl=max(posl,tmpl);
                    int tmpr=QueryMin(r+1,n,s[i]);
                    // for(int x:s[i]) cout<<x<<' ';cout<<": "<<tmpr<<endl;
                    if(tmpr) posr=min(posr,tmpr); 
                }
                // cout<<posl<<' '<<posr<<endl;
                int ans=1e9;
                if(posl!=0) ans=min(ans,abs(l-posl)+abs(r-posl));
                if(posr!=n+1) ans=min(ans,abs(posr-l)+abs(posr-r));
                if(ans==1e9) cout<<-1<<endl;
                else cout<<ans<<endl;
            }
        }
    }
}