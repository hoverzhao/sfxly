#include<iostream>
using namespace std;
const int M=105;
int i,j,n,W;//n表示n个物品，W表示背包的容量
double w[M],v[M];//w[i] 表示第i个物品的重量，v[i] 表示第i个物品的价值
bool x[M];  //x[i]表示第i个物品是否放入背包
double cw;  //当前重量
double cp;  //当前价值
double bestp;  //当前最优价值
bool bestx[M]; //当前最优解

double Bound(int i){//计算上界（即已装入物品价值+剩余物品的总价值）
    //剩余物品为第i~n种物品
    int rp=0;
    while(i<=n){//依次计算剩余物品的价值
        rp+=v[i];
        i++;
    }
    return cp+rp;
}

void Backtrack(int t){//用于搜索空间数，t表示当前扩展结点在第t层
    if(t>n){//已经到达叶子结点
        for(j=1;j<=n;j++)
            bestx[j]=x[j];
        bestp=cp;//保存当前最优解
        return ;
    }
    if(cw+w[t]<=W){//如果满足约束条件则搜索左子树
        x[t]=1;
        cw+=w[t];
        cp+=v[t];
        Backtrack(t+1);
        cw-=w[t];
        cp-=v[t];
    }
    if(Bound(t+1)>bestp){//如果满足限界条件则搜索右子树
        x[t]=0;
        Backtrack(t+1);
    }
}

void Knapsack(double W, int n){
    cw=0;//初始化当前放入背包的物品重量为0
    cp=0; //初始化当前放入背包的物品价值为0
    bestp=0; //初始化当前最优值为0
    double sumw=0.0; //用来统计所有物品的总重量
    double sumv=0.0; //用来统计所有物品的总价值
    for(i=1;i<=n;i++){
        sumv+=v[i];
        sumw+=w[i];
    }
    if(sumw<=W){
        bestp=sumv;
        cout<<"放入背包的物品最大价值为: "<<bestp<<endl;
        cout<<"所有的物品均放入背包。";
        return;
    }
    Backtrack(1);
    cout<<"放入背包的物品最大价值为: "<<bestp<<endl;
    cout<<"放入背包的物品序号为: ";
    for(i=1;i<=n;i++){ //输出最优解
        if(bestx[i]==1)
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(){
    cout<<"请输入物品的个数n和背包的容量W:";
    cin>>n>>W;
    cout<<"请依次输入每个物品的重量w和价值v,用空格分开:"<<endl;
    for(i=1;i<=n;i++)
        cin>>w[i]>>v[i];
    Knapsack(W,n);
    return 0;
}
/*测试数据
4 10
2 6
5 3
4 5
2 4
*/
