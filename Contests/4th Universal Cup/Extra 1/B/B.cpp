#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define dbg cerr<<"LINE "<<__LINE__<<":"
using namespace std;
//typedef long long ll;
const int N=2000009,inf=1e9,mod=998244353;
int n,cntc[N],cntw[N],cntp[N];
string str; 
int mn,mx;
int check(int len){
    for(int i=1;i+len-1<=n;i++){
        int j=i+len-1;
        if(i<=mn&&j>=mx) ;
        else continue;
        int cC=cntc[j]-cntc[i-1];
        int cW=cntw[j]-cntw[i-1];
        int cP=cntp[j]-cntp[i-1];
        int valc=cC-cW-cP,valw=cW-cC-cP,valp=cP-cC-cW;
        valc+=(i-1>=1&&str[i-1]=='C')+(j+1<=n&&str[j+1]=='C');
        valw+=(i-1>=1&&str[i-1]=='W')+(j+1<=n&&str[j+1]=='W');
        valp+=(i-1>=1&&str[i-1]=='P')+(j+1<=n&&str[j+1]=='P');
        if(valc<=1&&valw<=1&&valp<=1) return i;
    }
    return 0;
}
inline void Insert(string &s,int &t,char c){
	string res;
	if(t){
		res.push_back(s.front());
		for(int i=1;i<s.size();i++){
			if(s[i-1]==s[i]){
				if(t) res.push_back(c),t--;
			}
			res.push_back(s[i]);
		}
		s=res;
		res.clear();
	}
	if(t){
		res.push_back(s.front());
		for(int i=1;i<s.size();i++){
			if(s[i-1]!=c&&s[i]!=c){
				if(t) res.push_back(c),t--;
			}
			res.push_back(s[i]);
		}
		s=res;
		res.clear();
	}
	if(t){
		if(s.front()!=c){
			res.push_back(s.front());
			while(t) res.push_back(c),t--;
			for(int i=1;i<s.size();i++) res.push_back(s[i]);
			s=res;
		}else{
			for(int i=0;i+1<s.size();i++) res.push_back(s[i]);
			while(t) res.push_back(c),t--;
			res.push_back(s.back());
			s=res;
		}
	}
}
void sol(int l,int r){
	char c[3]={'C','W','P'};
	int t[3]={0,0,0};
	t[0]=cntc[r]-cntc[l-1];
	t[1]=cntw[r]-cntw[l-1];
	t[2]=cntp[r]-cntp[l-1];
	map<char,int> id;
	for(int i:{0,1,2}) id[c[i]]=i;
	string now;
	if(l==1) now.push_back('#');
	else now.push_back(str[l-1]);
	if(r==n) now.push_back('#');
	else now.push_back(str[r+1]);
	// cerr<<"Solve "<<l<<' '<<r<<endl;
	// cerr<<now<<endl;
	if(now.front()!='#') Insert(now,t[id[now.front()]],now.front());
	// cerr<<now<<endl;
	if(now.back()!='#') Insert(now,t[id[now.back()]],now.back());
	// cerr<<now<<endl;
	for(int i:{0,1,2}) Insert(now,t[i],c[i]);
	// cerr<<now<<endl;
	for(int i=l;i<=r;i++) str[i]=now[i-l+1];
}
void solve(){
    cin>>n;cin>>str;str=" "+str;
    for(int i=1;i<=n;i++){
        cntc[i]=cntc[i-1]+(str[i]=='C');
        cntw[i]=cntw[i-1]+(str[i]=='W');
        cntp[i]=cntp[i-1]+(str[i]=='P');
    }mn=n+1,mx=0;
    for(int i=2;i<=n;i++){
        if(str[i]==str[i-1]){
            mn=min(mn,i);
            mx=max(mx,i);
        }
    }
    mx--;
    if(mn==n+1&&mx==-1){
        cout<<"Beautiful\n";
        return;
    }
    int l=1,r=n;
    pair<int,int> ans={0,0};
    while(l<=r){
        int mid=(l+r)>>1;
        int g=check(mid);
        if(g){
            r=mid-1;
            ans=mp(g,g+mid-1);
        }
        else l=mid+1;
    }
    if(ans==mp(0,0)){
        cout<<"Impossible\n";
    }
    else{
		cout<<"Possible"<<endl;
        cout<<ans.first<<" "<<ans.second<<"\n";
        sol(ans.first,ans.second);
		cout<<str.substr(1)<<endl;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _; cin>>_; while(_--)
    solve();
    return 0;
}