#include<iostream>
#include <iomanip>
using namespace std;
int n,m,cnt=0,s;
char core;
struct Edge{
	int to,w,next;
}edge[500000];
int head[500000];
int dis[100000];
bool vis[100000];
void init() ;
void add_edge(int ,int ,int );
int main(){
    cin>>n>>m>>core;
	s=int(core)-64;
    init();
	for(int i=1;i<=m;i++){
		char u,v;
		int w;
		cin>>u>>v>>w;
		add_edge(int(u)-64,int(v)-64,w);
		add_edge(int(v)-64,int(u)-64,w);
	}
    int pos=s;
    dis[s]=0;
    while(vis[pos]==0){
		long long minn=0xffff;
		vis[pos]=1;
		for(int i=head[pos];i!=0;i=edge[i].next ){
			if(!vis[edge[i].to]&&dis[edge[i].to]>dis[pos]+edge[i].w)
	    		dis[edge[i].to]=dis[pos]+edge[i].w;
	 	} 
	 	for(int i=1;i<=n;i++){
	 		if(dis[i]<minn && vis[i]==0){
	 			minn=dis[i];
				pos=i;
	 		}
		}
	} 
	for(int i=1;i<=26;i++){
		if(i== int('O'-64)){
			cout<<left<<setw(5)<<"VA";
			continue;
		}
		if(i==int('N'-64) || i==int('I'-64)|| i==int('K'-64))
			continue;
		cout<<left<<setw(5)<<char(i+64);
	}
	cout<<endl;
	for(int i=1;i<=26;i++){
		if(i==int('N'-64) || i==int('I'-64)|| i==int('K'-64) )
			continue;
		cout<<left<<setw(4)<<dis[i]<<" ";
	}
	cout<<endl;
	return 0;
}


void init() {
	for(int i=0;i<=n;i++)
		head[i]=0;
	for(int i=1;i<=n;i++){
        dis[i]=0xffff;
    }
}
void add_edge(int x,int y,int z){
	cnt++;
	edge[cnt].to=y;
	edge[cnt].w=z;
	edge[cnt].next=head[x];
	head[x]=cnt;
}









