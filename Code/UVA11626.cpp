#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

struct Node{
	double x,y,k;
}p[N];
bool Cmp(Node i,Node j){
	if(i.k==j.k)return i.y>j.y;
	return i.k<j.k;
}

int main(){
	int T;
    cin>>T;
	while(T--){
		int sm=0,sn=1,n;
		cin>>n;
		for(int i=1;i<=n;i++){
			double tx,ty;char temp;
			cin>>tx>>ty>>temp;
			if(temp=='N')continue;
			p[++sm].x=tx,p[sm].y=ty;
			if(p[sm].x<p[sn].x)sn=sm;
			else if(p[sm].x==p[sn].x&&p[sm].y<p[sn].y)sn=sm;
		}

		p[0]=p[sn];
		for(int i=1;i<=sm;i++){
			double x=p[i].x-p[0].x;
			double y=p[i].y-p[0].y;
			if(x==0)p[i].k=1e8;
			else p[i].k=y/x;
		}
		sort(p+1,p+sm+1,Cmp);

		cout<<sm<<endl;
		cout<<(int)p[0].x<<' '<<(int)p[0].y<<endl;
		for(int i=1;i<=sm;i++){
            if(!(p[i].x==p[0].x&&p[0].y==p[i].y)){
                cout<<(int)p[i].x<<' '<<(int)p[i].y<<endl;
            }
        }
	}

	return 0;
}