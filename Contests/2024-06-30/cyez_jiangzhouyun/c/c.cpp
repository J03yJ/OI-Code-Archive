// #pragma GCC optimize(3)
// #pragma GCC target("avx")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("inline")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-ffast-math")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("-falign-jumps")
// #pragma GCC optimize("-falign-loops")
// #pragma GCC optimize("-falign-labels")
// #pragma GCC optimize("-fdevirtualize")
// #pragma GCC optimize("-fcaller-saves")
// #pragma GCC optimize("-fcrossjumping")
// #pragma GCC optimize("-fthread-jumps")
// #pragma GCC optimize("-funroll-loops")
// #pragma GCC optimize("-fwhole-program")
// #pragma GCC optimize("-freorder-blocks")
// #pragma GCC optimize("-fschedule-insns")
// #pragma GCC optimize("inline-functions")
// #pragma GCC optimize("-ftree-tail-merge")
// #pragma GCC optimize("-fschedule-insns2")
// #pragma GCC optimize("-fstrict-aliasing")
// #pragma GCC optimize("-fstrict-overflow")
// #pragma GCC optimize("-falign-functions")
// #pragma GCC optimize("-fcse-skip-blocks")
// #pragma GCC optimize("-fcse-follow-jumps")
// #pragma GCC optimize("-fsched-interblock")
// #pragma GCC optimize("-fpartial-inlining")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC optimize("-freorder-functions")
// #pragma GCC optimize("-findirect-inlining")
// #pragma GCC optimize("-fhoist-adjacent-loads")
// #pragma GCC optimize("-frerun-cse-after-loop")
// #pragma GCC optimize("inline-small-functions")
// #pragma GCC optimize("-finline-small-functions")
// #pragma GCC optimize("-ftree-switch-conversion")
// #pragma GCC optimize("-foptimize-sibling-calls")
// #pragma GCC optimize("-fexpensive-optimizations")
// #pragma GCC optimize("-funsafe-loop-optimizations")
// #pragma GCC optimize("inline-functions-called-once")
// #pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>

using namespace std;

ifstream fin("c.in");
ofstream fout("c.out");
#define cin fin
#define cout fout

#define int long long
const int N=2e5+9;
const long long p=998244353;

int a[N],cnt[16],cnt123[16],cnt124[30][4],cnt134[30][30][2],cnt12[16];
int cnt234[30][30][30],cnt13[30][2];
bitset<N> b[30],r[30],tmp[30],atmp[30],TEMP[4];

signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    if(k==1){
        int ans=0;
        for(int d=0;d<=30;d++){
            int cnt=0;
            for(int i=1;i<=n;i++) if(a[i]>>d&1) cnt++;
            ans=(ans+((1<<d)%p)*(2*cnt*(n-cnt)%p)%p)%p;
        }
        cout<<ans<<endl;
    }else if(k==2){
        int ans=0;
        for(int d=0;d<=30;d++){
            int cnt=0;
            for(int i=1;i<=n;i++) if(a[i]>>d&1) cnt++;
            ans=(ans+((1<<d)%p*(1<<d)%p)*(2*cnt*(n-cnt)%p)%p)%p;
        }
        for(int d1=0;d1<=30;d1++){
            for(int d2=d1+1;d2<=30;d2++){
                int cnt1=0,cnt2=0,cnt3=0,cnt124=0;
                for(int i=1;i<=n;i++){
                    bool f1=a[i]>>d1&1,f2=a[i]>>d2&1;
                    if(f1&&f2) cnt1++;
                    else if(f1) cnt2++;
                    else if(f2) cnt3++;
                    else cnt124++;
                }
                ans=(ans+((1<<d1)%p*(1<<d2)%p)*(4*cnt1*cnt124%p)%p)%p;
                ans=(ans+((1<<d1)%p*(1<<d2)%p)*(4*cnt2*cnt3%p)%p)%p;
            }
        }
        cout<<ans<<endl;
    }else if(k==3){
        int ans=0;
        for(int i=0;i<30;i++){
            for(int j=1;j<=n;j++) b[i][j]=a[j]>>i&1,r[i][j]=!b[i][j];
        }
        for(int d1=0;d1<30;d1++){
            int cnt[2]={0,0};
            cnt[0]=r[d1].count();
            cnt[1]=b[d1].count();
            ans=(ans+(1<<d1)%p*(1<<d1)%p*(1<<d1)%p*cnt[0]%p*cnt[1]%p*2%p)%p;
        }
        for(int d1=0;d1<30;d1++){
            for(int d2=d1+1;d2<30;d2++){
                tmp[0]=r[d1]&r[d2];
                tmp[1]=r[d1]&b[d2];
                tmp[2]=b[d1]&r[d2];
                tmp[3]=b[d1]&b[d2];
                int cnt[4]={0,0,0,0};
                cnt[0]=tmp[0].count();
                cnt[1]=tmp[1].count();
                cnt[2]=tmp[2].count();
                cnt[3]=tmp[3].count();
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d2)%p*cnt[0]%p*cnt[3]%p*6%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*cnt[0]%p*cnt[3]%p*6%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d2)%p*cnt[1]%p*cnt[2]%p*6%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*cnt[1]%p*cnt[2]%p*6%p)%p;
                for(int d3=d2+1;d3<30;d3++){
                    int cnt[8]={0,0,0,0,0,0,0,0};
                    cnt[0]=(tmp[0]&r[d3]).count();
                    cnt[1]=(tmp[0]&b[d3]).count();
                    cnt[2]=(tmp[1]&r[d3]).count();
                    cnt[3]=(tmp[1]&b[d3]).count();
                    cnt[4]=(tmp[2]&r[d3]).count();
                    cnt[5]=(tmp[2]&b[d3]).count();
                    cnt[6]=(tmp[3]&r[d3]).count();
                    cnt[7]=(tmp[3]&b[d3]).count();
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*cnt[0]%p*cnt[7]%p*12%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*cnt[1]%p*cnt[6]%p*12%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*cnt[2]%p*cnt[5]%p*12%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*cnt[3]%p*cnt[4]%p*12%p)%p;
                }
            }
        }
        cout<<ans<<endl;
    }else{
        int ans=0,cl=0,CL=0;
        for(int i=0;i<30;i++){
            for(int j=1;j<=n;j++) b[i][j]=a[j]>>i&1,r[i][j]=!b[i][j];
        }
        for(int d1=0;d1<30;d1++){
            int cnt[2]={0,0};
            cnt[0]=r[d1].count();
            cnt[1]=b[d1].count();
            ans=(ans+(1<<d1)%p*(1<<d1)%p*(1<<d1)%p*(1<<d1)%p*cnt[0]%p*cnt[1]%p*2%p)%p;
        }
        for(int d2=1;d2<30;d2++){
            for(int d3=d2+1;d3<30;d3++){
                TEMP[0]=r[d2]&r[d3];
                for(int d4=d3+1;d4<30;d4++){
                    cnt234[d2][d3][d4]=(TEMP[0]&r[d4]).count();
                }
            }
        }
        for(int d1=0;d1<30;d1++){
            for(int d3=d1+2;d3<30;d3++){
                TEMP[0]=r[d1]&r[d3];
                TEMP[1]=b[d1]&r[d3];
                cnt13[d3][0]=TEMP[0].count();
                cnt13[d3][1]=TEMP[1].count();
                for(int d4=d3+1;d4<30;d4++){
                    cnt134[d3][d4][0]=(TEMP[0]&r[d4]).count();
                    cnt134[d3][d4][1]=(TEMP[1]&r[d4]).count();
                }
            }
            for(int d2=d1+1;d2<30;d2++){
                tmp[0]=r[d1]&r[d2];
                tmp[1]=b[d1]&r[d2];
                tmp[2]=r[d1]&b[d2];
                tmp[3]=b[d1]&b[d2];
                int cnt[4]={0,0,0,0};
                cnt[0]=tmp[0].count();
                cnt[1]=tmp[1].count();
                cnt[2]=tmp[2].count();
                cnt[3]=tmp[3].count();
                cnt12[0]=cnt[0];
                cnt12[1]=cnt[1];
                cnt12[2]=cnt[2];
                cnt12[3]=cnt[3];
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d2)%p*(1<<d2)%p*cnt[0]%p*cnt[3]%p*8%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*(1<<d1)%p*cnt[0]%p*cnt[3]%p*8%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*(1<<d2)%p*cnt[0]%p*cnt[3]%p*12%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d2)%p*(1<<d2)%p*cnt[1]%p*cnt[2]%p*8%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*(1<<d1)%p*cnt[1]%p*cnt[2]%p*8%p)%p;
                ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d1)%p*(1<<d2)%p*cnt[1]%p*cnt[2]%p*12%p)%p;
                for(int d4=d2+2;d4<30;d4++){
                    cnt124[d4][0]=(tmp[0]&r[d4]).count();
                    cnt124[d4][1]=(tmp[1]&r[d4]).count();
                    cnt124[d4][2]=(tmp[2]&r[d4]).count();
                    cnt124[d4][3]=(tmp[3]&r[d4]).count();
                }
                // int T=clock();
                for(int d3=d2+1;d3<30;d3++){
                    atmp[0]=tmp[0]&r[d3];
                    cnt[0]=atmp[0].count();
                    cnt[1]=(tmp[1]&r[d3]).count();
                    cnt[2]=cnt13[d3][0]-cnt[0];
                    cnt[3]=cnt13[d3][1]-cnt[1];
                    cnt[4]=cnt12[0]-cnt[0];
                    cnt[5]=cnt12[1]-cnt[1];
                    cnt[6]=cnt12[2]-cnt[2];
                    cnt[7]=cnt12[3]-cnt[3];
                    cnt123[0]=cnt[0];
                    cnt123[1]=cnt[1];
                    cnt123[2]=cnt[2];
                    cnt123[3]=cnt[3];
                    cnt123[4]=cnt[4];
                    cnt123[5]=cnt[5];
                    cnt123[6]=cnt[6];
                    cnt123[7]=cnt[7];
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d1)%p*cnt[0]%p*cnt[7]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d2)%p*cnt[0]%p*cnt[7]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d3)%p*cnt[0]%p*cnt[7]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d1)%p*cnt[1]%p*cnt[6]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d2)%p*cnt[1]%p*cnt[6]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d3)%p*cnt[1]%p*cnt[6]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d1)%p*cnt[2]%p*cnt[5]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d2)%p*cnt[2]%p*cnt[5]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d3)%p*cnt[2]%p*cnt[5]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d1)%p*cnt[3]%p*cnt[4]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d2)%p*cnt[3]%p*cnt[4]%p*24%p)%p;
                    ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d3)%p*cnt[3]%p*cnt[4]%p*24%p)%p;
                    // int t=clock();
                    for(int d4=d3+1;d4<30;d4++){
                        cnt[0]=(atmp[0]&r[d4]).count();
                        cnt[1]=cnt234[d2][d3][d4]-cnt[0];
                        cnt[2]=cnt134[d3][d4][0]-cnt[0];
                        cnt[3]=cnt134[d3][d4][1]-cnt[1];
                        cnt[4]=cnt124[d4][0]-cnt[0];
                        cnt[5]=cnt124[d4][1]-cnt[1];
                        cnt[6]=cnt124[d4][2]-cnt[2];
                        cnt[7]=cnt124[d4][3]-cnt[3];
                        cnt[8]=cnt123[0]-cnt[0];
                        cnt[9]=cnt123[1]-cnt[1];
                        cnt[10]=cnt123[2]-cnt[2];
                        cnt[11]=cnt123[3]-cnt[3];
                        cnt[12]=cnt123[4]-cnt[4];
                        cnt[13]=cnt123[5]-cnt[5];
                        cnt[14]=cnt123[6]-cnt[6];
                        cnt[15]=cnt123[7]-cnt[7];
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[0]%p*cnt[15]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[1]%p*cnt[14]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[2]%p*cnt[13]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[3]%p*cnt[12]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[4]%p*cnt[11]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[5]%p*cnt[10]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[6]%p*cnt[9]%p*48%p)%p;
                        ans=(ans+(1<<d1)%p*(1<<d2)%p*(1<<d3)%p*(1<<d4)%p*cnt[7]%p*cnt[8]%p*48%p)%p;
                    }
                    // cl+=clock()-t;
                }
                // CL+=clock()-T;
            }
        }
        // cout<<cl<<' '<<CL<<endl;
        cout<<ans<<endl;
    }
    return 0;
}