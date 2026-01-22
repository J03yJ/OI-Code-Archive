#include<bits/stdc++.h>

using namespace std;

const int N=5e1+9;
const int B=5e1;
#define endl '\n'

int a[N],n,k;
vector<int> ans;
void Work(int pos){
    ans.push_back(pos);
    swap(a[pos+1],a[pos]);
    a[pos]+=k;
}
void Sort(int m){
    if(a[m]<=a[m+1]&&a[m+1]<=a[m+2]) return ;
    if(a[m]>=a[m+2]&&a[m+2]>=a[m+1]){
        Work(m);
        Work(m+1);
        Work(m+1);
    }
    if(a[m+1]>=a[m+2]&&a[m+2]>=a[m]){
        Work(m);
        Work(m+1);
    }
    if(a[m]>=a[m+1]&&a[m+1]>=a[m+2]){
        Work(m);
        Work(m+1);
        Work(m+1);
    }
    if(a[m+2]>=a[m]&&a[m]>=a[m+1]){
        Work(m);
        Work(m+1);
        Work(m+1);
    }
    if(a[m+1]>=a[m]&&a[m]>=a[m+2]){
        Work(m+1);
        Work(m);
        Work(m+1);
        Work(m+1);
        Work(m+1);
        Work(m+1);
    }
    return ;
}
void Plus(int m){
    Work(m+1);
    Work(m);
    Work(m);
    Work(m+1);
    Work(m);
    Work(m);
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(n==2){
        if(a[1]<=a[2]){
            cout<<"Yes"<<endl;
            cout<<0<<endl;
        }else{
            a[2]+=k;
            swap(a[1],a[2]);
            if(a[1]<=a[2]){
                cout<<"Yes"<<endl;
                cout<<1<<endl;
                cout<<1<<endl;
            }else{
                cout<<"No"<<endl;
            }
        }
        return 0;
    }
    Sort(1);
    for(int i=n%3+1;i<=n;i+=3){
        Sort(i);
        while(a[i]<a[i-1]) Plus(i);
    }

    cout<<"Yes"<<endl;
    cout<<ans.size()<<endl;
    for(int x:ans) cout<<x<<endl;

    return 0;
}