#include<bits/stdc++.h>

using namespace std;

// ifstream fin("ramsey.in");
// ofstream fout("ramsey.out");
// #define cin fin
// #define cout fout

const int n=64,lim=5;
int bel[n+1];
bool Check(){
    vector<int> a[lim];
    for(int i=1;i<=n;i++) a[bel[i]].push_back(i);
    for(int k=0;k<lim;k++){
        for(int i=0;i<a[k].size();i++){
            for(int j=i+1;j<a[k].size();j++){
                if(bel[a[k][i]^a[k][j]]==k) return 0;
            }
        }
    }
    return 1;
}

int main(){
    int p[lim+1]={0,13,26,39,52,64};
    for(int i=0;i<lim;i++){
        for(int j=p[i]+1;j<=p[i+1];j++) bel[j]=i;
    }
    srand(time(0));
    random_shuffle(bel+1,bel+n+1);
    // do{
    //     for(int i=1;i<=n;i++) cout<<bel[i]<<' ';cout<<endl;
    //     if(Check()) break ;
    // }while(next_permutation(bel+1,bel+n+1));
    do{
        for(int i=1;i<=n;i++) cout<<bel[i]<<' ';cout<<endl;
        if(Check()) break ;
    }while(random_shuffle(bel+1,bel+n+1),1);
    for(int i=1;i<=n;i++) cout<<bel[i]<<' ';cout<<endl;
    system("pause");
    return 0;
}

// int main(){
//     int mask[32]={0,1,0,1,3,0,3,3,2,3,1,2,3,1,2,0,0,0,1,2,1,3,0,0,3,2,0,1,2,1,2,2};
//     for(int i=0;i<32;i++){
//         for(int j=i+1;j<32;j++){
//             cout<<mask[i^j]<<' ';
//         }
//         cout<<endl;
//     }
//     return 0;
// }