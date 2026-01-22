#include<bits/stdc++.h>

using namespace std;

ifstream fin("quicksort.in");
ofstream fout("quicksort.out");
#define cin fin
#define cout fout

const int N=5e5+9;

int cnt;
int P(vector<int> &a,int l,int r){
    int p=a[l+r>>1];
    int i=l-1,j=r+1;
    while(true){
        do{
            i++;
        }while(a[i]<p);
        do{
            j--;
        }while(a[j]>p);
        if(i>=j) return j;
        swap(a[i],a[j]);
        cnt++;
    }
}
void QSort(vector<int> &a,int l,int r){
    if(l>=0&&r>=0&&l<r){
        int p=P(a,l,r);
        QSort(a,l,p);
        QSort(a,p+1,r);
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        cnt=0;
        int n;
        cin>>n;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++) cin>>a[i];

        QSort(a,1,n);
        cout<<cnt<<endl;
    }

    return 0;
}