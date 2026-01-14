#include<bits/stdc++.h>

using namespace std;

const int p=1e9+7;
const int K=109;
const int N=1e4+9;

int f[N][K][3],a[N];

int main(){
	string S;cin>>S;S=" "+S;
    int P;cin>>P;
	int n=S.size()-1;

	for(int i=1;i<=n;++i) a[i]=S[i]-'0';

	f[0][0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<P;j++){
			for(int k=0;k<10;k++){
				int J=((j-k)%P+P)%P;
				(f[i][j][0]+=f[i-1][J][0])%=p;
				if(k<a[i]) (f[i][j][0]+=f[i-1][J][1])%=p;
			}
			f[i][j][1]=f[i-1][((j-a[i])%P+P)%P][1];
		}
	}

	cout<<((f[n][0][1]+f[n][0][0]-1)%p+p)%p<<endl;
    
    return 0;
}