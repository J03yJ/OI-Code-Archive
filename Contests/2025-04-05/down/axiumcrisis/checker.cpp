/*
 *
 *  Please use it on Windows or Linux only.
 *  I don't know if it can work on Mac cause I have never had it used yet.
 *  Myee Ye, 2023.6.1.
 *
 */

#include <algorithm>
#include <stdio.h>
#include <vector>

FILE*fin,*fout,*fans,*fscore,*freport=stderr;
int full_score;

void EXIT(){
    if(fscore)fflush(fscore);
    if(freport!=stderr)fflush(freport);
    fclose(fin);
    fclose(fout);
    fclose(fans);
    if(fscore)fclose(fscore);
    if(freport!=stderr)fclose(freport);
    exit(0);
}

void AC(){
    if(fscore)fprintf(fscore,"%d",full_score);
    fprintf(freport,"Accepted.\n");
    EXIT();
}

void WA(){
    if(fscore)fprintf(fscore,"0");
    fprintf(freport,"Wrong Answer.\n");
    EXIT();
}

void FAIL(){
    if(fscore)fprintf(fscore,"0");
    fprintf(freport,"Wrong Output Format.\n");
    EXIT();
}

void WA(const char*S){
    if(fscore)fprintf(fscore,"0");
    fprintf(freport,"%s",S);
    EXIT();
}

int readInt(FILE*fin){
    int ans;
    if(fscanf(fin,"%d",&ans)!=1)
        FAIL();
    return ans;
}

int readInt(int l,int r,FILE*fin){
    int ans;
    if(fscanf(fin,"%d",&ans)!=1)
        FAIL();
    if(ans<l||ans>r)
        FAIL();
    return ans;
}

char nextChar(FILE*f){
    char c;
    while(~(c=fgetc(f))&&c)if(c!=' '&&c!='\n'&&c!='\r'&&c)
        return c;
    return c;
}

void AC_try(){
    char c=nextChar(fout);
    if(c&&~c&&c!=' '&&c!='\n'&&c!='\r')
        FAIL();
    AC();
} 

int n,c;
int U[18],V[18],W[18];bool G[18];
std::vector<int>E[18];
int Nxt[18][18];
void dfs(int p,int f)
{
    if(p==f)Nxt[f][p]=-1;
    for(auto e:E[p])if(e!=Nxt[f][p])Nxt[f][U[e]^V[e]^p]=e,dfs(U[e]^V[e]^p,f);
}
int Son[2][18],tp;
void clear(){tp=0;}
int NewNode()
{
    Son[0][tp]=Son[1][tp]=-1;return tp++;
}

void check()
{
    n=readInt(fin);
    for(int i=1;i<n;i++)
        U[i]=readInt(fin),V[i]=readInt(fin),W[i]=readInt(fin);
    int ans=readInt(fans);
    if(readInt(1,n,fout)!=ans)WA();
    if(c)
    {
        int m=readInt(0,n-1,fout);
        for(int i=1;i<n;i++)if(W[i]<=1)
        {
            if(W[i]!=readInt(0,1,fout))WA("You replace a edge that colored yet!\n");
        }else W[i]=readInt(0,1,fout);
        for(int i=0;i<n;i++)
            E[i].clear();
        for(int i=1;i<n;i++)
            E[U[i]].push_back(i),E[V[i]].push_back(i),G[i]=false;
        for(int i=0;i<n;i++)
            dfs(i,i);
        clear(),NewNode();
        while(m--)
        {
            int u=readInt(0,n-1,fout);
            int v=readInt(0,n-1,fout);
            if(u==v)WA("u == v in your scheme!\n");
            int r=0;
            while(v!=u)
                if(G[Nxt[v][u]])WA("You cover one edge more than once!\n");
                else
                {
                    int&s=Son[W[Nxt[v][u]]][r];
                    if(!~s)s=NewNode();
                    r=s;
                    G[Nxt[v][u]]=true;
                    u^=U[Nxt[v][u]]^V[Nxt[v][u]];
                }
        }
        if(ans!=tp)
            WA();
    }
}

int main(int argc,char**argv){
    if(argc<4){
        // fprintf(stderr,"What are you fucking doing???\n");
        fprintf(stderr,"Unexpected Error: argc should be at least 4.\n");
        fprintf(stderr,"Correct Way to Call it:\n");
        fprintf(stderr,"Linux   : ./checker [input] [output] [answer]\n");
        fprintf(stderr,"Windows :   checker [input] [output] [answer]\n");
        fprintf(stderr,"Lemon   :   checker [input] [output] [answer] [full_score] [score] [report]\n");
        return 0;
    }
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"r");
    fans=fopen(argv[3],"r");
    if(argc>=5)sscanf(argv[4],"%d",&full_score);
    if(argc>=6)fscore=fopen(argv[5],"w");
    if(argc>=7)freport=fopen(argv[6],"w");
    int t=readInt(fin);c=readInt(fin),readInt(fin);
    while(t--)
        check();
    AC_try();
    return 0;
}
