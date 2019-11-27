#include<stdio.h>
#include<stdlib.h> 
#include<malloc.h>
#define MaxSize 100
#define M 8
#define N 8
typedef struct
{
	int i, j;    //方块在迷宫中的坐标位置(i,j)         
	int pre;    //本路径中上一方块在队列中的下标   
} SqQueue;
SqQueue Qu[MaxSize];  //定义顺序非循环队列
int front = 0, rear = 0;
int mg[M + 2][N + 2] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};
void print(SqQueue Qu[], int front)
{
	int k = 0;
	for (int i = front; i > 0; i = Qu[i].pre)
	{
		printf("(%d,%d) ", Qu[i].i, Qu[i].j);
		k++;
		if (k % 5 == 0)   //每输出每5个方块后换一行
			printf("\n");
	}
}
bool mgpath1(int xi, int yi, int xe, int ye)	//搜索路径为:(xi,yi)->(xe,ye)
{
	int i, j, di, i1, j1;
	rear++;
	Qu[rear].i = xi; Qu[rear].j = yi; Qu[rear].pre = 1; //(xi,yi)进队
	mg[xi][yi] = -1;		        //将其赋值-1,以避免回过来重复搜索
	while (front != rear)		    //队不空循环
	{
		front++;
		i = Qu[front].i; j = Qu[front].j; //出队
		if (i == xe && j == ye)	    //找到了出口,输出路径
		{
			print(Qu, front);	//调用print函数输出路径
			return true;		//找到一条路径时返回真
		}
		for (di = 0; di < 8; di++)    //循环扫描每个方位
		{
			switch (di)
			{
			case 0:i1 = i - 1;   j1 = j; break;
			case 1:i1 = i;  j1 = j + 1; break;
			case 2:i1 = i + 1;  j1 = j; break;
			case 3:i1 = i;   j1 = j - 1; break;
			case 4:i1 = i - 1;   j1 = j-1; break;
			case 5:i1 = i-1;  j1 = j +1; break;
			case 6:i1 = i + 1;  j1 = j-1; break;
			case 7:i1 = i +1;   j1 = j + 1; break;
			}
			if (mg[i1][j1] == 0)
			{
				rear++;
				Qu[rear].i = i1; Qu[rear].j = j1;
				Qu[rear].pre = front;	//(i1，j1)方块进队
				mg[i1][j1] = -1;	//将其赋值-1
			}
		}//for
	}//while
	return false;
}//mgpath1

int main()
{
	if (!mgpath1(1, 1, M, N))
		printf("该迷宫问题没有解!");
	system("pause");
	return 1;
}