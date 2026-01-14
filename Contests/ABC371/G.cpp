#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int inf=1e9;

int a[N],p[N],ans[N],n;
bool vis[N];

int F(vector<int> &a){
    int n=a.size();
    int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		if(a[(i+k)%n]==a[(j+k)%n]) k++;
		else{
			if(a[(i+k)%n]<a[(j+k)%n]) j+=k+1;
			else i+=k+1;
			if(i==j) i++;
			k=0;
		}
	}
    return min(i,j);
}
int GCD(int x,int y){
    if(!y) return x;
    else return GCD(y,x%y);
}

int main(){
    cin>>n;
    for(int i=1,x;i<=n;i++) cin>>x,p[x]=i;
    for(int i=1;i<=n;i++) cin>>a[i];

    int r=1,cur=0;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue ;
        vector<int> v;
        int x=i;
        while(!vis[x]){
            vis[x]=1;
            v.push_back(x);
            x=p[x];
        }
        int g=GCD(r,v.size());
        vector<int> u,mp;
        for(int i=0,cnt=0;i<v.size();i++){
            if(cur%g==i%g) u.push_back(a[v[i]]),mp.push_back(cnt++);
            else u.push_back(inf),mp.push_back(0);
        }
        int pos=F(u);
        for(int j=0;j<v.size();j++){
            ans[v[j]]=a[v[(j+pos)%v.size()]];
        }
        cur+=mp[pos]*r;
        r*=v.size()/g;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}