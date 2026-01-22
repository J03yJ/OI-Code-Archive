#include<bits/stdc++.h>

using namespace std;

ofstream fout("quicksort.in");
#define cout fout

int main(){
    srand(time(0));
    int n;
    cin>>n;
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    // random_shuffle(a.begin(),a.end());
    reverse(a.begin(),a.end());
    cout<<1<<endl<<n<<endl;
    for(int x:a) cout<<x<<' ';cout<<endl;
    return 0;
}