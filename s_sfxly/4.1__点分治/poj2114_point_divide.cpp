#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=10005;
int cnt,n,k,ans,head[maxn];
int root,S,size[maxn],f[maxn],d[maxn],dep[maxn];
bool vis[maxn];
struct edge{
	int to,next,w;
}edge[maxn*2];

void add(int u,int v,int w){
	edge[++cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].next=head[u];
	head[u]=cnt;
}

void getroot(int u,int fa){//获取重心
    size[u]=1;
	f[u]=0;//删除u后，最大子树的大小 
    for(int i=head[u];i;i=edge[i].next){
    	int v=edge[i].to;
    	if(v!=fa&&!vis[v]){
            getroot(v,u);
            size[u]+=size[v];
       		f[u]=max(f[u],size[v]);
        }
	}    
    f[u]=max(f[u],S-size[u]);//S为当前子树总结点数 
    if(f[u]<f[root])
		root=u;
}

void getdep(int u,int fa){//获取距离
    dep[++dep[0]]=d[u];//保存距离数组 
    for(int i=head[u];i;i=edge[i].next){
    	int v=edge[i].to;
    	if(v!=fa&&!vis[v]&&d[u]+edge[i].w<=k){
    		d[v]=d[u]+edge[i].w;
            getdep(v,u);
		}
    }
}

int getsum(int u,int dis){ //获取u的子树中满足条件的个数
    d[u]=dis;
	dep[0]=0;
	getdep(u,0);
    sort(dep+1,dep+1+dep[0]);
    int L=1,R=dep[0],sum=0;
    while(L<R){
    	if(dep[L]+dep[R]<k)
			L++;
		else if(dep[L]+dep[R]>k)
			R--;
		else{
			if(dep[L]==dep[R]){//两端相等,区间中间也相等,n(n-1)/2
				sum+=(R-L+1)*(R-L)/2;
				break;
			}
			int st=L,ed=R;
			while(dep[st]==dep[L])//找左侧第一个不相等的数 
				st++;
			while(dep[ed]==dep[R])//找右侧第一个不相等的数
				ed--;
			sum+=(st-L)*(R-ed);
			L=st,R=ed;
		}	
	}
    return sum; 
}

void solve(int u){ //获取答案
    vis[u]=true;
	ans+=getsum(u,0);
    for(int i=head[u];i;i=edge[i].next){
    	int v=edge[i].to;
		if(!vis[v]){
			ans-=getsum(v,edge[i].w);//减去重复
            root=0;
			S=size[v];
			getroot(v,u);
            solve(root);
		}
    }
}

int main(){
	int y,w;
	while(scanf("%d",&n)&&n){
		memset(head,0,sizeof(head));
		cnt=0;
        for(int i=1;i<=n;i++){
           while(scanf("%d",&y)&&y){
		   		scanf("%d",&w);
            	add(i,y,w);
				add(y,i,w);
		   }
        }
        while(scanf("%d",&k)&&k){
        	memset(vis,0,sizeof(vis));
        	f[0]=0x3f3f3f3f;//初始化树根
        	root=0;
			S=n;
			ans=0;
			getroot(1,0);
			solve(root);
			if(ans)
				printf("AYE\n");
			else
				printf("NAY\n");
		}
        printf(".\n");
    }
    return 0;
}
